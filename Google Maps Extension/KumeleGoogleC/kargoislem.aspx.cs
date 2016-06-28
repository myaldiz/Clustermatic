using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.IO;
using System.Text;

public partial class kargoislem : System.Web.UI.Page
{

    class BenimClass //gridView'e datasource olarak bağlayabilmek için gerekli class
    {
        private string satir;
        public string Msatir
        {
            set {satir=value;}
            get { return satir;}            
        }
        private string sira;
        public string Msira
        {
            set { sira = value; }
            get { return sira; }
        }
        private string islem;
        public string Mislem
        {
            set { islem = value; }
            get { return islem; }
        }

        private string koord;
        public string Mkoord
        {
            set { koord = value; }
            get { return koord; }
        }
    }
    void KargoDurumGrupKoordinatDosyasiOlustur()
    {    
        string[] Satirlar;
        int i;        
        if (!File.Exists(Server.MapPath("~\\data\\KargoGrupKoordinatlar.txt")))
            {
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
    
        
    void DosyaDuzenle(int satir,string islem)
    { 
        string[] Satirlar;
        string yeniSatir;
        string DosyaAdi = Server.MapPath("~\\data\\KargoGrupKoordinatlar.txt");
        Satirlar = File.ReadAllLines(DosyaAdi, Encoding.GetEncoding(1254));
        yeniSatir= islem + "/" + Satirlar[satir].Substring(2);
        Satirlar[satir] = yeniSatir;
        File.Delete(DosyaAdi);
        File.WriteAllLines(DosyaAdi,Satirlar);
    }

    void ComboDoldur()
    {
        string[] Satirlar;
        string DosyaAdi = Server.MapPath("~\\data\\KargoGrupKoordinatlar.txt");
        int grupSayi = 0;        
        Satirlar = File.ReadAllLines(DosyaAdi, Encoding.GetEncoding(1254));
        drpGrup.Items.Clear();

        for (int i = 0; i < Satirlar.Length; i++)
        {
            if (Satirlar[i] == "<group>")
            {
                grupSayi++;                
                ListItem ComboListe = new ListItem();
                ComboListe.Text = "Group " + grupSayi.ToString();
                ComboListe.Value = grupSayi.ToString();
                drpGrup.Items.Add(ComboListe);
            }            
        }        
    }

    void kargoIslem(int grupNo) //grup noyu parametre olarak alıyor
    { 
        string[] Satirlar;
        string DosyaAdi = Server.MapPath("~\\data\\KargoGrupKoordinatlar.txt");
        int grupSayi=0;
        int sira = 0;
        
        Satirlar = File.ReadAllLines(DosyaAdi, Encoding.GetEncoding(1254));
        
        List<BenimClass> liste = new List<BenimClass>();

        for (int i = 0; i < Satirlar.Length; i++)
        {
            if (Satirlar[i] == "<group>")
            {
                grupSayi++;                
            }
            if (grupSayi == grupNo && Satirlar[i] != "<group>" && Satirlar[i] != "</group>") //istediğimiz grup ve koordinat ise
            {
                sira++;
                BenimClass getir = new BenimClass();
                getir.Msira = sira.ToString();
                getir.Msatir = i.ToString() ;
                getir.Mkoord = Satirlar[i].Substring(2); //dosyadaki koordinat bilgisi al index 2'den itibaren koordinat bilgisi var
                getir.Mislem = Satirlar[i].Substring(0,1); //işareti oku
                liste.Add(getir);
            }            
        }
        grdKargo.DataSource = liste;
        grdKargo.DataBind();            
    }

    protected void Page_Load(object sender, EventArgs e)
    {
        if (Request.QueryString["satir"] != null)
        {
            DosyaDuzenle(int.Parse(Request.QueryString["satir"]), Request.QueryString["islem"]);
        }        
        
        if (!Page.IsPostBack)
        {
           ComboDoldur(); // sayfa ilk yüklendiğinde doldur.
           if (Session["secim"] != null)
           {
               drpGrup.SelectedValue = (string)Session["secim"];
               kargoIslem(int.Parse((string)Session["secim"]));
           }
           else
           {
               kargoIslem(1); // sayfa ilk yüklendiğinde 1. grubu göster.
           }           

         }
        KargoDurumGrupKoordinatDosyasiOlustur(); //kargo işlem takibi için text dosya oluşmadıysa kontrol edip oluştur.
    }

    protected void drpGrup_SelectedIndexChanged(object sender, EventArgs e)
    {
        kargoIslem(int.Parse(drpGrup.SelectedValue));
        Session["secim"] = drpGrup.SelectedValue;
    }
}