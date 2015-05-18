/*
 * =====================================================================================
 *
 *       Filename:  evusbstream.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年02月07日 19时26分21秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */

#define DEFAULT_DEVICE "/dev/video0"

#include "UsbStream.hpp"

#define WIDTH 720
#define HEIGHT 480

int convert_yuv_to_rgb_pixel(int y, int u, int v)
{
     unsigned int pixel32 = 0;
     unsigned char *pixel = (unsigned char *)&pixel32;
     int r, g, b;
     r = y + (1.370705 * (v-128));
     g = y - (0.698001 * (v-128)) - (0.337633 * (u-128));
     b = y + (1.732446 * (u-128));
     if(r > 255) r = 255;
     if(g > 255) g = 255;
     if(b > 255) b = 255;
     if(r < 0) r = 0;
     if(g < 0) g = 0;
     if(b < 0) b = 0;
     pixel[0] = r * 220 / 256;
     pixel[1] = g * 220 / 256;
     pixel[2] = b * 220 / 256;
     return pixel32;
}

int yuvtorgb0(unsigned char *yuv, unsigned char *rgb, unsigned int width, unsigned int height)
{
    unsigned int in, out = 0;
    unsigned int pixel_16;
    unsigned char pixel_24[3];
    unsigned int pixel32;
    int y0, u, y1, v;
    for(in = 0; in < width * height * 2; in += 4) {
        pixel_16 =
            yuv[in + 3] << 24 |
            yuv[in + 2] << 16 |
            yuv[in + 1] <<  8 |
            yuv[in + 0];
        y0 = (pixel_16 & 0x000000ff);
        u  = (pixel_16 & 0x0000ff00) >>  8;
        y1 = (pixel_16 & 0x00ff0000) >> 16;
        v  = (pixel_16 & 0xff000000) >> 24;
        pixel32 = convert_yuv_to_rgb_pixel(y0, u, v);
        pixel_24[0] = (pixel32 & 0x000000ff);
        pixel_24[1] = (pixel32 & 0x0000ff00) >> 8;
        pixel_24[2] = (pixel32 & 0x00ff0000) >> 16;
        rgb[out++] = pixel_24[0];
        rgb[out++] = pixel_24[1];
        rgb[out++] = pixel_24[2];
        pixel32 = convert_yuv_to_rgb_pixel(y1, u, v);
        pixel_24[0] = (pixel32 & 0x000000ff);
        pixel_24[1] = (pixel32 & 0x0000ff00) >> 8;
        pixel_24[2] = (pixel32 & 0x00ff0000) >> 16;
        rgb[out++] = pixel_24[0];
        rgb[out++] = pixel_24[1];
        rgb[out++] = pixel_24[2];
    }
    return 0;
}

int spliteY(unsigned char * yuv, unsigned char* y, unsigned int width, unsigned int height)
{
	unsigned int in,out = 0;
	unsigned int pixel_16;
	unsigned char pixel_24;
	unsigned int pixel32;
	int y0,u,y1,v;
	for(in = 0; in<width*height*2;in +=4)
	{
		pixel_16 = 
			yuv[in+3]<<24 | 
			yuv[in+2]<<16 |
			yuv[in+1]<< 8 |
			yuv[in+0];
		y0 = (pixel_16 & 0x000000ff);
		u  = (pixel_16 & 0x0000ff00) >>  8;
		y1 = (pixel_16 & 0x00ff0000) >> 16;
		v  = (pixel_16 & 0xff000000) >> 24;
		y[out++] = y0;
		y[out++] = y1;
	}

}

CUsbStream::CUsbStream()
{
	n_buffer=0;
	device=new char(20);
	device=DEFAULT_DEVICE;
	p=new uchar[WIDTH*HEIGHT*3+1];
   	m_height=HEIGHT;
    	m_width=WIDTH;
	videoProc = new CVideoProc();

	/* init font */
    	cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,2);

	/* init video writer */
	//video = cvCreateVideoWriter("test.avi",CV_FOURCC('D','I','V','X'),20,cvSize(720,480),1);

}

CUsbStream::~CUsbStream()
{
	delete device;
	delete p;
	delete videoProc;
}

void CUsbStream::Process()
{
    int fd = this->open_camer_device();
    this->init_camer_device(fd);
    this->start_capturing(fd);
    this->mainloop(fd);
    this->stop_capturing(fd);
    this->uninit_camer_device(fd);
    this->close_camer_device(fd);
}

void CUsbStream::set_device(char* device_name)
{
	device=device_name;
}

int CUsbStream::open_camer_device()
{
	int fd;

	if((fd = open(device,O_RDWR | O_NONBLOCK)) < 0)
	{
		perror("Fail to open");
		exit(EXIT_FAILURE);
	} 
	return fd;
}

void CUsbStream::close_camer_device(int fd)
{
	if(-1 == close(fd))
	{
		perror("Fail to close fd");
		exit(EXIT_FAILURE);
	}
	return;
}

int CUsbStream::init_mmap(int fd)
{
	int i = 0;
	struct v4l2_requestbuffers reqbuf;

	bzero(&reqbuf,sizeof(reqbuf));
	reqbuf.count = 1;
	reqbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	reqbuf.memory = V4L2_MEMORY_MMAP;
	//申请视频缓冲区(这个缓冲区位于内核空间，需要通过mmap映射)
	//这一步操作可能会修改reqbuf.count的值，修改为实际成功申请缓冲区个数
	if(-1 == ioctl(fd,VIDIOC_REQBUFS,&reqbuf))
	{
		perror("Fail to ioctl 'VIDIOC_REQBUFS'");
		exit(EXIT_FAILURE);
	}
	n_buffer = reqbuf.count;
	printf("n_buffer = %d\n",n_buffer);

	user_buf = (BUFTYPE*)calloc(reqbuf.count,sizeof(*user_buf));
	if(user_buf == NULL){
		fprintf(stderr,"Out of memory\n");
		exit(EXIT_FAILURE);
	}

	//将内核缓冲区映射到用户进程空间
	for(i = 0; i < reqbuf.count; i ++)
	{
		struct v4l2_buffer buf;
		bzero(&buf,sizeof(buf));
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index = i;
		//查询申请到内核缓冲区的信息
		if(-1 == ioctl(fd,VIDIOC_QUERYBUF,&buf))
		{
			perror("Fail to ioctl : VIDIOC_QUERYBUF");
			exit(EXIT_FAILURE);
		}

		user_buf[i].length = buf.length;
		user_buf[i].start = 
		mmap(
		NULL,/*start anywhere*/
		buf.length,
		PROT_READ | PROT_WRITE,
		MAP_SHARED,
		fd,buf.m.offset);
		if(MAP_FAILED == user_buf[i].start)
		{
			perror("Fail to mmap");
			exit(EXIT_FAILURE);
		}
	}	

	return 0;
}

//初始化视频设备
int CUsbStream::init_camer_device(int fd)
{
	struct v4l2_fmtdesc fmt;
	struct v4l2_capability cap;
	struct v4l2_format stream_fmt;
	int ret;
	//当前视频设备支持的视频格式
	memset(&fmt,0,sizeof(fmt));
	fmt.index = 0;
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	while((ret = ioctl(fd,VIDIOC_ENUM_FMT,&fmt)) == 0)
	{
		fmt.index ++ ;

		printf("{pixelformat = %c%c%c%c},description = '%s'\n",
		fmt.pixelformat & 0xff,(fmt.pixelformat >> 8)&0xff,
		(fmt.pixelformat >> 16) & 0xff,(fmt.pixelformat >> 24)&0xff,
		fmt.description);
	}

	//查询视频设备驱动的功能
	ret = ioctl(fd,VIDIOC_QUERYCAP,&cap);
	if(ret < 0){
		perror("FAIL to ioctl VIDIOC_QUERYCAP");
		exit(EXIT_FAILURE);
	}

	//判断是否是一个视频捕捉设备
	if(!(cap.capabilities & V4L2_BUF_TYPE_VIDEO_CAPTURE))
	{
		printf("The Current device is not a video capture device\n");
		exit(EXIT_FAILURE);
	}

	//判断是否支持视频流形式
	if(!(cap.capabilities & V4L2_CAP_STREAMING))
	{
		printf("The Current device does not support streaming i/o\n");
		exit(EXIT_FAILURE);
	}

	//设置摄像头采集数据格式，如设置采集数据的
	//长,宽，图像格式(JPEG,YUYV,MJPEG等格式)
	stream_fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	stream_fmt.fmt.pix.width = m_width;
	stream_fmt.fmt.pix.height = m_height;
    	stream_fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV; //YUV422
    	stream_fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;

	if(-1 == ioctl(fd,VIDIOC_S_FMT,&stream_fmt))
	{
		perror("Fail to ioctl");
		exit(EXIT_FAILURE);
	}
	//初始化视频采集方式(mmap)
	init_mmap(fd);

	return 0;
}

int CUsbStream::start_capturing(int fd)
{
	unsigned int i;
	enum v4l2_buf_type type;

	//将申请的内核缓冲区放入一个队列中
	for(i = 0;i < n_buffer;i ++)
	{
		struct v4l2_buffer buf;

		bzero(&buf,sizeof(buf));
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index = i;
		if(-1 == ioctl(fd,VIDIOC_QBUF,&buf))
		{
			perror("Fail to ioctl 'VIDIOC_QBUF'");
			exit(EXIT_FAILURE);
		}
	}

	//开始采集数据
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if(-1 == ioctl(fd,VIDIOC_STREAMON,&type))
	{
		printf("i = %d.\n",i);
		perror("Fail to ioctl 'VIDIOC_STREAMON'");
		exit(EXIT_FAILURE);
	}

	return 0;
}

//将采集好的数据放到文件中
int CUsbStream::process_image(void *addr,int length)
{
	/* For gray frame */
    	m_Image = cvCreateImageHeader(cvSize(WIDTH,HEIGHT),IPL_DEPTH_8U,1);
    	delete p;
    	p=new uchar[m_height*m_width];
    	spliteY((uchar*)addr,p,m_width,m_height);
	cvSetData(m_Image,p,m_width);
	/********** For rgb frame *********
	m_Image = cvCreateImageHeader(cvSize(WIDTH,HEIGHT),IPL_DEPTH_8U,3);
	delete p;
	p=new uchar[m_height*m_width*3+1];
	yuvtorgb0((unsigned char*)addr,p,m_width,m_height);
	cvSetData(m_Image,p,m_width*3);
	************************************/

	/* video process */
	videoProc->Process(m_Image);
	
	/* write date and time */
	/* init date */
    	time_t t=time(0);
    	strftime(datentime,sizeof(datentime),"%Y-%m-%d %H:%M:%S",localtime(&t));
    	cvPutText(m_Image,datentime,cvPoint(15,50),&font,CV_RGB(255,0,0));

	cvShowImage("Video Frame",m_Image);
	
	/* save video */
	//cvWriteFrame(video,m_Image);

    	cvWaitKey(1);
	return 0;
}

int CUsbStream::read_frame(int fd)
{
	struct v4l2_buffer buf;
	unsigned int i;

	bzero(&buf,sizeof(buf));
	buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	buf.memory = V4L2_MEMORY_MMAP;
	//从队列中取缓冲区
	if(-1 == ioctl(fd,VIDIOC_DQBUF,&buf))
	{
		perror("Fail to ioctl 'VIDIOC_DQBUF'");
		exit(EXIT_FAILURE);
	}

	assert(buf.index < n_buffer);
	//读取进程空间的数据到一个文件中
    process_image(user_buf[buf.index].start,buf.length);
	if(-1 == ioctl(fd,VIDIOC_QBUF,&buf))
	{
		perror("Fail to ioctl 'VIDIOC_QBUF'");
		exit(EXIT_FAILURE);
	}

	return 1;
}

int CUsbStream::mainloop(int fd)
{ 
    int count=100;
	clock_t startTime,finishTime;
	double selectTime,frameTime;

    while(count>0)
	{
		for(;;)
		{
			fd_set fds;
			struct timeval tv;
			int r;
			FD_ZERO(&fds);
			FD_SET(fd,&fds);


			tv.tv_sec=5;
			tv.tv_usec=0;
			r=select(fd+1,&fds,NULL,NULL,&tv);
			if(-1==r)
			{
				if(EINTR==errno)
					continue;
				perror("Fail to select");
				exit(EXIT_FAILURE);
			}
			if(0==r)
			{
				fprintf(stderr,"select TimeOut\n");
				exit(EXIT_FAILURE);
			}
            if(read_frame(fd))
                break;
		}
	}
	return 0;
}

void CUsbStream::stop_capturing(int fd)
{
	enum v4l2_buf_type type;
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if(-1 == ioctl(fd,VIDIOC_STREAMOFF,&type))
	{
		perror("Fail to ioctl 'VIDIOC_STREAMOFF'");
		exit(EXIT_FAILURE);
	}
	return;
}

void CUsbStream::uninit_camer_device(int fd)
{
	unsigned int i;

	for(i = 0;i < n_buffer;i ++)
	{
		if(-1 == munmap(user_buf[i].start,user_buf[i].length))
		{
			exit(EXIT_FAILURE);
		}
	}
	free(user_buf);
	return;
}


