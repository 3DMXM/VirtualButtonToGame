unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, ExtDlgs;

type
  TForm1 = class(TForm)
    Timer1: TTimer;
    GroupBox1: TGroupBox;
    RadioButton1: TRadioButton;
    RadioButton2: TRadioButton;
    RadioButton3: TRadioButton;
    RadioButton4: TRadioButton;
    RadioButton5: TRadioButton;
    Button2: TButton;
    Button1: TButton;
    RadioButton6: TRadioButton;
    Edit1: TEdit;
    Button3: TButton;
    OpenTextFileDialog1: TOpenTextFileDialog;
    procedure FormCreate(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure Button2Click(Sender: TObject);
    procedure RadioButton1Click(Sender: TObject);
    procedure RadioButton2Click(Sender: TObject);
    procedure RadioButton3Click(Sender: TObject);
    procedure RadioButton4Click(Sender: TObject);
    procedure RadioButton5Click(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure RadioButton6Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);

    procedure Test();            //增强功能示例
    procedure GetDDFunAddress(); //获取DD函数地址

  private
    { Private declarations }

  public
    { Public declarations }
  end;

  // 定义 DD 函数
  TDD_todc = function(vkcode:integer):integer;stdcall;
  TDD_mov = function(x,y:integer):integer;stdcall;
  TDD_btn = function(btn:integer):integer;stdcall;
  TDD_whl = function(whl:integer):integer;stdcall;
  TDD_key = function(key,flag:integer):integer;stdcall;
  TDD_str = function(str:AnsiString):integer;stdcall;
  TDD_movR = function(dx,dy:integer):integer;stdcall;

  TDD_MouseMove = function(hwnd:THandle;x:integer;y:integer):integer;stdcall;
  TDD_SnapPic = function(hwnd:THandle;x,y,w,h:integer):integer;stdcall;
  TDD_PickColor = function(hwnd:THandle;x,y:integer;m:integer=0):integer;stdcall;
  TDD_GetActiveWindow = function():THandle;stdcall;


var
  Form1: TForm1;

var
  DD:Thandle;      //链接库句柄

  DD_todc:TDD_todc;
  DD_mov:TDD_mov;  //鼠标绝对移动
  DD_btn:TDD_btn;
  DD_whl:TDD_whl;
  DD_key:TDD_key;
  DD_str:TDD_str;
  DD_movR:TDD_movR; //鼠标相对移动

  DD_MouseMove:TDD_MouseMove;
  DD_SnapPic:TDD_SnapPic;
  DD_PickColor:TDD_PickColor;
  DD_GetActiveWindow:TDD_GetActiveWindow;

  select:integer;   //功能选择
implementation

{$R *.dfm}

procedure TForm1.FormCreate(Sender: TObject);

begin
  Button2.Enabled:=false;
  Button1.Enabled:=false;
end;

procedure TForm1.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  if DD  <> 0 then
  begin
    freelibrary(DD );
  end;

  Timer1.Enabled := false;

end;

procedure TForm1.Button2Click(Sender: TObject);
begin
   Timer1.Enabled := false;
   Button1.Enabled:=true;
   Button2.Enabled:=false;
end;

procedure TForm1.Button3Click(Sender: TObject);
var
  filename:PWideChar;

begin
  if OpenTextFileDialog1.Execute then
  begin
    filename:= PWideChar(OpenTextFileDialog1.FileName);
    Edit1.Text:=filename;

    DD:=Loadlibrary( filename);

    if (DD  <> 0)  then
    begin
        MessageBox(0,'载入DD链接库成功','提示',MB_ICONASTERISK);
        GetDDFunAddress();
    end
    else
    begin
        MessageBox(0,'载入DD链接库错误','提示',MB_ICONASTERISK);
    end;
  end;
end;

procedure TForm1.RadioButton1Click(Sender: TObject);
begin
 select:=1;
end;

procedure TForm1.RadioButton2Click(Sender: TObject);
begin
 select:=2;
end;

procedure TForm1.RadioButton3Click(Sender: TObject);
begin
 select:=3;
end;

procedure TForm1.RadioButton4Click(Sender: TObject);
begin
 select:=4;
end;

procedure TForm1.RadioButton5Click(Sender: TObject);
begin
 select:=5;
end;

procedure TForm1.RadioButton6Click(Sender: TObject);
begin
 select :=6;
end;

procedure TForm1.Timer1Timer(Sender: TObject);
var
  ddcode :integer;
begin
   case select of
     1:   DD_movR(20,20)  ;   //鼠标移动

     2:
     begin                      //鼠标点击
          DD_btn(1)  ;
          DD_btn(2)  ;
     end;

     3:                         //鼠标滚轮
     begin
          DD_whl(1)  ;
          DD_whl(2)  ;
     end;

     4:                         //键盘按键
     begin
          ddcode := 300;        // TAB键在DD键码表3区第1位置
          ddcode := DD_todc(VK_TAB);  //或通过函数从虚拟键码转换
          DD_key(ddcode,1)  ;         // 1按下，2放开
          DD_key(ddcode,2)  ;
     end;

     5:  DD_str('KeyBorad !@#*| ') ;      //模拟打字

     6:  test();
   end;
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
  Timer1.Enabled := true;
  Button2.Enabled:=true;
  Button1.Enabled:=false;
end;

procedure TForm1.Test();
var
  hwnd:THandle;
  clr:TColor;

begin
  hwnd:=0;   // 等于0时表示全屏坐标，否则以窗口为坐标
  hwnd:=DD_GetActiveWindow ;  //当用普通API函数无法获取当前激活窗口句柄时，可用这个函数。

  DD_MouseMove(hwnd,100,100);//移动鼠标，当hwnd=0时，等同DD_mov
  DD_SnapPic(hwnd,100,100,50,100);//抓图，保存在c:\dd snap 文件夹

  clr:=DD_PickColor(hwnd,100,100); //以全屏或窗口坐标取色
  self.Color:=clr;

end;

procedure TForm1.GetDDFunAddress();
var
  hwnd:THandle;
begin
  @DD_mov:=nil;  //鼠标移动
  @DD_movR:=nil;  //鼠标移动
  @DD_btn:=nil;  //鼠标按键 1左下 2左上 4右下 8右上
  @DD_whl:=nil;  //鼠标滚轮
  @DD_key:=nil;  //键盘按键
  @DD_str:=nil;  //输入键盘上可见字符
  @DD_todc:=nil; //转换虚拟键码到DD键码

  @DD_MouseMove:=nil;    //增强鼠标移动
  @DD_SnapPic:=nil;      //抓图，保存目录 C:\DD Snap
  @DD_PickColor:=nil;    // 取色
  @DD_GetActiveWindow:=nil;   //获取激活窗口句柄

 if DD <> 0 then
 begin
    @DD_mov:=GetprocAddress(dd,'DD_mov');
    @DD_btn:=GetprocAddress(dd,'DD_btn');
    @DD_whl:=GetprocAddress(dd,'DD_whl');
    @DD_key:=GetprocAddress(dd,'DD_key');
    @DD_str:=GetprocAddress(dd,'DD_str');
    @DD_movR:=GetprocAddress(dd,'DD_movR');
    @DD_todc:=GetprocAddress(dd,'DD_todc');

    @DD_MouseMove:=GetprocAddress(dd,'DD_MouseMove');
    @DD_SnapPic:=GetprocAddress(dd,'DD_SnapPic');
    @DD_PickColor:=GetprocAddress(dd,'DD_PickColor');
    @DD_GetActiveWindow:=GetprocAddress(dd,'DD_GetActiveWindow');

    if ( Assigned(@DD_mov) and Assigned(@DD_btn) and
         Assigned(@DD_whl) and Assigned(@DD_key) and
         Assigned(@DD_str) and Assigned(@DD_movR) and  Assigned(@DD_todc))then
    begin
     MessageBox(0,'DD 获取通用函数地址成功','提示',MB_ICONASTERISK);
     button1.Enabled := true;

      if ( Assigned(@DD_MouseMove) and Assigned(@DD_SnapPic)  and
         Assigned(@DD_PickColor) and Assigned(@DD_GetActiveWindow) )then
      begin
        MessageBox(0,'DD 获取增强函数地址成功','提示', MB_ICONASTERISK);
        RadioButton6.Enabled:= true;
      end;

    end;

 end;

end;

end.

