using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace App_csharp
{
    public partial class Form1 : Form
    {
        private CDD dd;

        public Form1()
        {
            InitializeComponent();
        }
 
        private void Form1_Load(object sender, EventArgs e)
        {
            this.button_start.Enabled = false;

            reg_hotkey();                            // 注册热键

            dd = new CDD();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            //dd.btn(-1);
            unreg_hotkey();
        }
        
        private void timer1_Tick(object sender, EventArgs e)
        {

            if (radioButton1.Checked == true)      // 测试键盘按键
            {
                int ddcode =  300;                         //tab键位在DD键码表的3区第1个位置
                dd.key(ddcode, 1);                              
                dd.key(ddcode, 2);                        // 1=按下 2=放开                    
                return;
            }

            if (radioButton2.Checked == true)     //测试鼠标点击
            {
                dd.btn(1);                                    // 1=左键按下
                dd.btn(2);                                    // 2=左键放开 
                return;
            }
                        
            if (radioButton3.Checked == true)    //测试鼠标移动
            {
                dd.movR(100,100);
                return;
            }
                   
            if (radioButton4.Checked == true)   //测试鼠标滚轮
            {
                dd.whl(1);                                  //前
                System.Threading.Thread.Sleep(1000);
                dd.whl(2);                                  //后
            }

        }

        private void button1_Click(object sender, EventArgs e)
        {
            //可从注册表中直接获取
            string dllfile = ReadDataFromReg();

            //LoadDllFile(dllfile);
            //return;

            //或手动定位
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "DD|*.DLL";

            if (ofd.ShowDialog() != DialogResult.OK)
            {
                return;
            }

            LoadDllFile(ofd.FileName);   
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (button_start.Text == "开始")
            {
                button_start.Text = "停止";
                timer1.Enabled = true;
            }
            else
            {
                button_start.Text = "开始";
                timer1.Enabled = false;
            }
        }
      
        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            string url = "http://" + linkLabel1.Text;
            System.Diagnostics.Process.Start(url);
        }

        private void LoadDllFile(string dllfile)
        {
            label1.Visible = false;
            label2.Visible = false;
            button_start.Enabled = false;

            System.IO.FileInfo fi = new System.IO.FileInfo(dllfile);
            if (!fi.Exists)
            {
                MessageBox.Show("文件不存在");
                return;
            }

            int ret = dd.Load(dllfile);
            //if (ret == -2) { MessageBox.Show("装载库时发生错误"); return; }
            //if (ret == -1) { MessageBox.Show("取函数地址时发生错误"); return; }


            button_start.Enabled = true;
            label1.Visible = true;
            label2.Visible = true;

            textBox1.Text = dllfile;
            dd.btn(0);   

            return;
        }

        private string ReadDataFromReg()
        {
            Microsoft.Win32.RegistryKey key;
            key = Microsoft.Win32.Registry.LocalMachine.OpenSubKey(@"SOFTWARE\\DD XOFT\\", false);
            if (key != null)
            {
                foreach (string vname in key.GetValueNames())
                {
                    if ("path" == vname.ToLower())
                    {
                        return key.GetValue(vname, "").ToString();
                    }
                }
            }
            return "";
        }

 #region "热键设置相关代码"
        [DllImport("user32.dll")]
        public static extern bool RegisterHotKey(
         IntPtr hWnd,
         int id,                            // 热键标识
         KeyModifiers modkey,  //  修改键
         Keys vk                         //  虚键码
        );
        [DllImport("user32.dll")]
        public static extern bool UnregisterHotKey(
         IntPtr hWnd,              // 窗口句柄 
         int id                          // 热键标识 
        );

        void reg_hotkey()
        {
            RegisterHotKey(this.Handle, 80, 0, Keys.F8);
            RegisterHotKey(this.Handle, 90, 0, Keys.F9);
            RegisterHotKey(this.Handle, 100, KeyModifiers.Shift | KeyModifiers.Control, Keys.B); //热键为SHIFT+CTRL+B
            RegisterHotKey(this.Handle, 200, KeyModifiers.Alt, Keys.D0);                                     //热键为Alt+0
        }

        void unreg_hotkey()
        {
            UnregisterHotKey(this.Handle, 80);
            UnregisterHotKey(this.Handle, 90);
            UnregisterHotKey(this.Handle, 100);
            UnregisterHotKey(this.Handle, 200);                     //缷载3个快捷键
        }

        protected override void WndProc(ref Message m)
        {
            const int WM_HOTKEY = 0x0312;                        //0x0312表示用户热键
            switch (m.Msg)
            {
                case WM_HOTKEY:
                    ProcessHotkey(m);                                      //调用ProcessHotkey()函数
                    break;
            }
            base.WndProc(ref m);
        }

        private void ProcessHotkey(Message msg)              //按下设定的键时调用该函数
        {
            switch (msg.WParam.ToInt32())
            {
                case 80:
                    Fun80();
                    break;
                case 90:
                    Fun90();                                                         //调用相关函数
                    break;
            }
        }

        private void Fun80()
        {
            dd.str("  Keyboard char [A-Za_z] {@$} ");
        }

        private void Fun90()
        {
            if (dd.key != null)
            {
                //模拟 系统热键 CTRL+ALT+DEL
                dd.key(600, 1);                                      // CTRL 键位在 6区1
                dd.key(602, 1);                                      // ALT   键位在 6区3
                dd.key(706, 1);                                      // DEL   键位在 7区7
                System.Threading.Thread.Sleep(5);
                dd.key(706, 2);
                dd.key(602, 2);
                dd.key(600, 2);
            }
        }

        #endregion

    }
}

