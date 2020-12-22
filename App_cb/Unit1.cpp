// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
}

void __fastcall TForm1::Button1Click(TObject *Sender) {

    OpenDialog1->Filter = "DD入口文件   (*.dll)|*.dll";
    OpenDialog1->DefaultExt = ".dll";

    this->Button2->Enabled = false;

    if (this->OpenDialog1->Execute()) {
	this->Edit1->Text = OpenDialog1->FileName;
	hinst = LoadLibrary(this->OpenDialog1->FileName.w_str());
	if (!hinst) {
	    ShowMessage("载入库时错误");
	    return;
	}

	dd_todc = (lpfun_DD_todc)GetProcAddress(hinst, "DD_todc");
	dd_btn = (lpfun_DD_btn)GetProcAddress(hinst, "DD_btn");
	dd_mov = (lpfun_DD_mov)GetProcAddress(hinst, "DD_mov");
	dd_movR = (lpfun_DD_mov)GetProcAddress(hinst, "DD_movR");
	dd_whl = (lpfun_DD_whl)GetProcAddress(hinst, "DD_whl");
	dd_key = (lpfun_DD_key)GetProcAddress(hinst, "DD_key");
	dd_str = (lpfun_DD_str)GetProcAddress(hinst, "DD_str");

	dd_MouseMove = (lpfun_DD_MouseMove)GetProcAddress(hinst,"DD_MouseMove");
	dd_SnapPic = (lpfun_DD_SnapPic)GetProcAddress(hinst, "DD_SnapPic");
	dd_PickColor = (lpfun_DD_PickColor)GetProcAddress(hinst,"DD_PickColor");
	dd_GetActiveWindow = (lpfun_DD_GetActiveWindow)GetProcAddress(hinst,"DD_GetActiveWindow");

	if (dd_todc && dd_movR && dd_btn && dd_mov && dd_whl && dd_key && dd_str)
	{
	    if (dd_MouseMove && dd_SnapPic && dd_PickColor && dd_GetActiveWindow) {
		ShowMessage("增强功能可用");
	    }

		this->Button2->Enabled = true;
		ShowMessage("驱动加载成功");

	}
	else {
	    ShowMessage("取函数地址有错误");
	}

    }
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender) {
    if (this->Button2->Caption == "开始") {
	this->Button2->Caption = "停止";
	this->Timer1->Enabled = true;
    }
    else {
	this->Button2->Caption = "开始";
	this->Timer1->Enabled = false;
    }
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender) {
    int ret;

    switch (this->RadioGroup1->ItemIndex) {
    case 0:              //鼠标按键
	ret = dd_btn(1); // 1,2,4,8 分别代表左下，左上，右下，右上
	ret = dd_btn(2);
	break;

    case 1:              //鼠标移动
	ret = dd_movR(100, 100);
	break;

    case 2:              //鼠标滚轮
	ret = dd_whl(1);
	ret = dd_whl(2);
	break;

    case 3:                    //模拟键盘TAB按键
       {
        int ddcode = 300;      //TAB键在第3排第1列
        ddcode = dd_todc(VK_TAB);  // 或通过函数转换
	ret = dd_key(ddcode, 1);  //  1==按下 ，2==放开
	ret = dd_key(ddcode, 2);
       }
       break;

    case 4:              //输入键盘可见字符
	ret = dd_str("123456789&!@#$%^&*(");
	break;

    case 5:             //示例代码，在增强版可用
	Demo();
    }

}

// ---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action) {
    if (this->Timer1->Enabled) {
	this->Timer1->Enabled = false;
    }
    if (hinst) {
	FreeLibrary(hinst);
    }
}

void __fastcall TForm1::Demo() {
    HWND h = dd_GetActiveWindow(); //获取当前激活窗口句柄，当用普通API无法获取时，可用这个函数

    int ret = 0;

    ret = dd_MouseMove(h,100,150); //以窗口为坐标移动鼠标，当h == 0 时表示以全屏为坐标

    ret = dd_SnapPic(h , 100,150,100,200); //以窗口为坐标抓图，当h==0 时，全屏抓图

    COLORREF clr = dd_PickColor(h, 100, 150); //取色

    this->Color = clr;

    return;
}
// ---------------------------------------------------------------------------
