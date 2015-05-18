/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  The main program
 *
 *        Version:  1.0
 *        Created:  2015年05月06日 12时29分09秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */

#include "UsbStream.hpp"

int main(int argc,char* argv[])
{
        CUsbStream* usbStream = new CUsbStream();
        usbStream->Process();
        delete usbStream;
	return 1;
}


