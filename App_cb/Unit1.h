// ---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>

// ---------------------------------------------------------------------------
class TForm1 : public TForm {
__published: // IDE-managed Components

    TTimer *Timer1;
    TEdit *Edit1;
    TButton *Button1;
    TOpenDialog *OpenDialog1;
    TButton *Button2;
    TRadioGroup *RadioGroup1;
    TLabel *Label1;

    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

private: // User declarations
	public : // User declarations
    __fastcall TForm1(TComponent* Owner);

    HINSTANCE hinst;

    typedef int(__stdcall*lpfun_DD_todc)(int);
    typedef int(__stdcall*lpfun_DD_btn)(int btn);
    typedef int(__stdcall*lpfun_DD_mov)(int x, int y);
    typedef int(__stdcall*lpfun_DD_movR)(int dx, int dy);
    typedef int(__stdcall*lpfun_DD_whl)(int whl);
    typedef int(__stdcall*lpfun_DD_key)(int code, int flag);
    typedef int(__stdcall*lpfun_DD_str)(char* str);

    typedef int(__stdcall*lpfun_DD_MouseMove)(HWND, int x, int y);
    typedef int(__stdcall*lpfun_DD_SnapPic)(HWND, int x, int y, int w, int h);
    typedef COLORREF(__stdcall *lpfun_DD_PickColor)(HWND, int x, int y,int mode = 0);
    typedef HWND(__stdcall *lpfun_DD_GetActiveWindow)();

    lpfun_DD_todc dd_todc;   //��׼�������תDD����
    lpfun_DD_mov dd_movR; //�������ƶ�
    lpfun_DD_btn dd_btn;      //��갴��
    lpfun_DD_mov dd_mov;   //�������ƶ�
    lpfun_DD_whl dd_whl;     //������
    lpfun_DD_key dd_key;     //���̰���
    lpfun_DD_str dd_str;       //���̿ɼ��ַ�

    //��ǿ����������
    lpfun_DD_MouseMove dd_MouseMove; //����ƶ�
    lpfun_DD_SnapPic dd_SnapPic;     //ץͼ
    lpfun_DD_PickColor dd_PickColor; //ȡɫ
    lpfun_DD_GetActiveWindow dd_GetActiveWindow;  //��ȡ��ǰ����ھ��

    void __fastcall Demo();
};

// ---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
// ---------------------------------------------------------------------------
#endif
