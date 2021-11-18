#include <iostream>
#include <Windows.h>
#include <setupapi.h>
#include <wdmguid.h>
#include <devguid.h>
#include <locale.h>

#pragma comment (lib, "setupapi.lib")
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int photoID = 1;
int videoID = 1;
bool isRecording = false;
int isVisible = 0;
HHOOK hook;

void GetCameraInfo()
{
	SP_DEVINFO_DATA DeviceInfoData = { 0 };
	HDEVINFO DeviceInfo = SetupDiGetClassDevsA(&GUID_DEVCLASS_CAMERA, "USB", NULL, DIGCF_PRESENT);
	if (DeviceInfo == INVALID_HANDLE_VALUE) {
		exit(1);
	}
	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	SetupDiEnumDeviceInfo(DeviceInfo, 0, &DeviceInfoData);
	char name[256];
	char manufacturer[256];
	SetupDiGetDeviceRegistryPropertyA(DeviceInfo, &DeviceInfoData, SPDRP_FRIENDLYNAME, NULL, (PBYTE)name, sizeof(name), 0);
	SetupDiGetDeviceRegistryPropertyA(DeviceInfo, &DeviceInfoData, SPDRP_MFG, NULL, (PBYTE)manufacturer, sizeof(manufacturer), 0);
	SetupDiDestroyDeviceInfoList(DeviceInfo);
	cout << "Manufacturer: " << manufacturer << '\n' << "Name: " << name << '\n';
}

void HiddenWorking(int key) {
	if (key == 1 || key == 2) {
		return;
	}
	VideoCapture webcam(0);
	Mat frame;
	switch (key) {
	case 48: {
		ShowWindow(FindWindowA("ConsoleWindowClass", NULL), isVisible);
		if (isVisible == 0) {
			isVisible = 1;
		}
		else {
			isVisible = 0;
		}
		break;
	}
	case 49: {
		webcam >> frame;
		imwrite("photo" + to_string(photoID++) + ".jpg", frame);
		break;
	}
	case 50: {
		if (isRecording) {
			isRecording = false;
		}
		else {
			isRecording = true;

			int w = webcam.get(CAP_PROP_FRAME_WIDTH);
			int h = webcam.get(CAP_PROP_FRAME_HEIGHT);
			string filename = "video" + to_string(videoID++) + ".avi";
			VideoWriter video(filename, VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(w, h));
			while (isRecording) {
				webcam >> frame;
				if (frame.empty()) break;
				video.write(frame);
				if ((char)waitKey(1) == 51) break;
			}
		}
		break;
	}
	case 27: exit(1); break;
	}
}

LRESULT _stdcall HookCallBack(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode >= 0) {
		if (wParam == WM_KEYDOWN) {
			KBDLLHOOKSTRUCT kbStruct = *((KBDLLHOOKSTRUCT*)lParam);
			HiddenWorking(kbStruct.vkCode);
		}
	}
	return CallNextHookEx(hook, nCode, wParam, lParam);
}

int main()
{
	setlocale(LC_ALL, "RUS");
	system("cls");
	GetCameraInfo();
	if (!(hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallBack, NULL, 0))) {
		return -1;
	}
	MSG msg;
	while (true) {
		GetMessage(&msg, NULL, 0, 0);
	}
	return 0;
}