using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace ARDUINO_RGB
{
    public partial class Form1 : Form
    {
        string Nombre, velocidad, dato, angulo;
        int R, G, B;

        public Form1()
        {
            InitializeComponent();
            PuertoSerie.Close();
            PuertoSerie.Dispose();
            Control.CheckForIllegalCrossThreadCalls = false;
            CheckForIllegalCrossThreadCalls = false;

            string[] Puertos = SerialPort.GetPortNames();
            foreach(string puerto in Puertos)
            {
                comboBox_Puerto.Items.Add(puerto);
            }

            comboBox_velocidad.Items.Insert(0, 9600);
            comboBox_velocidad.Items.Insert(1, 14400);
            
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            PuertoSerie.Write("1");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            PuertoSerie.Write("2");
        }

        private void button3_Click(object sender, EventArgs e)
        {
            angulo = comboBox1.Text;
            if (angulo == "0")
            {
                PuertoSerie.Write("0");
            }
            if (angulo == "90")
            {
                PuertoSerie.Write("3");
            }
            if (angulo == "180")
            {
                PuertoSerie.Write("4");
            }
        }

        private void comboBox_Puerto_SelectedIndexChanged(object sender, EventArgs e)
        {
            Nombre = comboBox_Puerto.Text;
            PuertoSerie.PortName = Nombre;
        }

        private void comboBox_velocidad_SelectedIndexChanged(object sender, EventArgs e)
        {
            velocidad = comboBox_velocidad.Text;
            PuertoSerie.BaudRate = Convert.ToInt32(velocidad);

        }

        private void buttonConectar_Click(object sender, EventArgs e)
        {
            try
            {
                CheckForIllegalCrossThreadCalls = false;

                PuertoSerie.Open();
                Console.Beep();
            }
            catch(Exception)
            {
                MessageBox.Show("Verifique la conexión", "Error");
            }
        }

        private void PuertoSerie_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            try
            {
                dato = PuertoSerie.ReadLine();

                if(dato.Contains("R"))
                {
                    dato = dato.Remove(0, 1);

                    R = Convert.ToInt32(dato);
                    trackBar_R.Value = R;
                    textBox_R.Text = dato;
                }
                if (dato.Contains("G"))
                {
                    dato = dato.Remove(0, 1);

                    G = Convert.ToInt32(dato);
                    trackBar_G.Value = G;
                    textBox_G.Text = dato;
                }
                if (dato.Contains("B"))
                {
                    dato = dato.Remove(0, 1);

                    B = Convert.ToInt32(dato);
                    trackBar_B.Value = B;
                    textBox_B.Text = dato;
                }

                pictureBox1.BackColor = Color.FromArgb(R, G, B);
            }
            catch(Exception)
            {

            }
        }

       

       
    }
}
