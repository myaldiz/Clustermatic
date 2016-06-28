using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.IO;
using System.Text;
using System.Runtime.Serialization.Formatters.Binary;

public partial class GrupKoordinatAktar : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }
    protected void btnGonder_Click(object sender, EventArgs e)
    {
        string dosyaadi;
        string[] Satirlar;
        int i;

        dosyaadi = Server.MapPath("~\\\\data\\GrupKoordinatlar.txt");

        if (!DosyaGonder.HasFile)
        {
            RegisterStartupScript("startupScript", "<script language=JavaScript>alert('Lütfen bilgi aktarılacak dosyayı seçiniz!');</script>");
            return;
        }                    

        if (File.Exists(dosyaadi))
        {
            File.Delete(dosyaadi);
        }
        DosyaGonder.PostedFile.SaveAs(dosyaadi);
        RegisterStartupScript("startupScript", "<script language=JavaScript>alert('Dosya Göderildi!');</script>");

        if (File.Exists(Server.MapPath("~\\data\\KargoGrupKoordinatlar.txt")))
        {
            File.Delete(Server.MapPath("~\\data\\KargoGrupKoordinatlar.txt")); //Var olanı sil
        }
        
        Satirlar = File.ReadAllLines(Server.MapPath("~\\data\\GrupKoordinatlar.txt"), Encoding.GetEncoding(1254));

        for (i=0; i<Satirlar.Length; i++)
        {
            if ((Satirlar[i].Trim() != "<group>") && (Satirlar[i].Trim() != "</group>") && Satirlar[i].Trim() != "")
            {
                Satirlar[i] = "1/" + Satirlar[i];            
            }
        }

        File.WriteAllLines(Server.MapPath("~\\data\\KargoGrupKoordinatlar.txt"), Satirlar);
   
    }
 }