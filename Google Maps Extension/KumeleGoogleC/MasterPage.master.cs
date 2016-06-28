using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.IO;
using System.Text;
using System.Runtime.Serialization.Formatters.Binary;

public partial class MasterPage : System.Web.UI.MasterPage
{
    protected void Page_Load(object sender, EventArgs e)
    {
        string MapCenter;
        if (Session["Login"] != "true")
        {
            Response.Redirect("Default.aspx");
        }
        if (File.Exists(Server.MapPath("~\\data\\Harita.txt")))
        {
            MapCenter = File.ReadAllText(Server.MapPath("~\\data\\Harita.txt"), Encoding.GetEncoding(1254));
        }
        else
        {
             MapCenter = "var zoomLevel = 14;\n var MapCenter = new google.maps.LatLng(41.0283, 28.8498);";
        }
        Session["MapCenter"] = MapCenter;
    }    
}
