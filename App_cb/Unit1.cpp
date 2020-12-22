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

    OpenDialog1->Filter = "DD����ļ�   (*.dll)|*.dll";
    OpenDialog1->DefaultExt = ".dll";

    this->Button2->Enabled = false;

    if (this->OpenDialog1->Execute()) {
	this->Edit1->Text = OpenDialog1->FileName;
	hinst = LoadLibrary(this->OpenDialog1->FileName.w_str());
	if (!hinst) {
	    ShowMessage("�����ʱ����");
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
		ShowMessage("��ǿ���ܿ���");
	    }

		this->Button2->Enabled = true;
		ShowMessage("�������سɹ�");

	}
	else {
	    ShowMessage("ȡ������ַ�д���");
	}

    }
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender) {
    if (this->Button2->Caption == "��ʼ") {
	this->Button2->Caption = "ֹͣ";
	this->Timer1->Enabled = true;
    }
    else {
	this->Button2->Caption = "��ʼ";
	this->Timer1->Enabled = false;
    }
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender) {
    int ret;

    switch (this->RadioGroup1->ItemIndex) {
    case 0:              //��갴��
	ret = dd_btn(1); // 1,2,4,8 �ֱ�������£����ϣ����£�����
	ret = dd_btn(2);
	break;

    case 1:              //����ƶ�
	ret = dd_movR(100, 100);
	break;

    case 2:              //������
	ret = dd_whl(1);
	ret = dd_whl(2);
	break;

    case 3:                    //ģ�����TAB����
       {
        int ddcode = 300;      //TAB���ڵ�3�ŵ�1��
        ddcode = dd_todc(VK_TAB);  // ��ͨ������ת��
	ret = dd_key(ddcode, 1);  //  1==���� ��2==�ſ�
	ret = dd_key(ddcode, 2);
       }
       break;

    case 4:              //������̿ɼ��ַ�
	ret = dd_str("123456789&!@#$%^&*(");
	break;

    case 5:             //ʾ�����룬����ǿ�����
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
    HWND h = dd_GetActiveWindow(); //��ȡ��ǰ����ھ����������ͨAPI�޷���ȡʱ�������������

    int ret = 0;

    ret = dd_MouseMove(h,100,150); //�Դ���Ϊ�����ƶ���꣬��h == 0 ʱ��ʾ��ȫ��Ϊ����

    ret = dd_SnapPic(h , 100,150,100,200); //�Դ���Ϊ����ץͼ����h==0 ʱ��ȫ��ץͼ

    COLORREF clr = dd_PickColor(h, 100, 150); //ȡɫ

    this->Color = clr;

    return;
}
// ---------------------------------------------------------------------------
