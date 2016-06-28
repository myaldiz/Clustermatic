using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.IO;
using System.Text;
using System.Runtime.Serialization.Formatters.Binary;

public partial class NoktalariBelirle : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        ltrParametreler.Text="<script>" + 
                              "</script>";
    }
    protected void Button1_Click(object sender, EventArgs e)
    {
        
        Response.Clear();
        Response.ContentType = "text/xml";
        Response.Charset = "iso-8859-9";
        Session.CodePage = 1254;
        Response.AddHeader("content-disposition", "attachment;filename=KOORDINATLAR.TXT");
        Response.Write(txtKoordinat.Text);
        Response.End();
    }
    protected void btnMesafeKaydet_Click(object sender, EventArgs e)
    {

    }
    protected void btnMapKaydet_Click(object sender, EventArgs e)
    {
        string MapCenter;
        MapCenter = "var zoomLevel = "+txtZoom.Text+";\n var MapCenter = new google.maps.LatLng("+txtCenter.Text+");";
       File.WriteAllText(Server.MapPath("~\\data\\Harita.txt"), MapCenter);
       Session["MapCenter"] = MapCenter;
        RegisterStartupScript("startupScript", "<script language=JavaScript>alert('Saved the new center point and zoom!');</script>");        
    }
}