//Copyright(c) 2015 ExtremeVision Ltd. All rights reserved.
//Use of the source code is governed by a LPGL-style.
//License that can be found in the LICENSE file.
//Author: Yun Luo(lauren.luo@extremevision.mo).

#include "usb_stream.h"

int main(int argc,char* argv[])
{
        CUsbStream* usbStream = new CUsbStream();
        //if(usbStream->set_save(2,"/root/videos/")==-1){
	//	cout<<"create save dir fail!"<<endl;
	//	return -1;
	//}
        usbStream->Process();
        delete usbStream;
	return 1;
}


