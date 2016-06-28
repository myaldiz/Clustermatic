using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.IO;
using System.Text;
using System.Runtime.Serialization.Formatters.Binary;

public partial class GrupYolTarifiMesafe : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {               
        string[] Satirlar;
        string kod="";        
        string kodPoligon="";
        string YolTarif1 = "";        
        int i=0;
        int gSayi=0;
        int elemanSira=0;
        Satirlar = File.ReadAllLines(Server.MapPath("~\\data\\GrupKoordinatlar.txt"), Encoding.GetEncoding(1254));
             
    
        for (i = 0;i<Satirlar.Length ; i++)
        {

            if (Satirlar[i].Trim() == "</group>")
            {                
          

                string renkDolgu = "";
                string renkLine="";
                string opacity="0.35";
                if (gSayi == 1) { renkLine = "#FF0066"; renkDolgu = "#FF0066"; opacity = "0.60"; } //pembe
                if (gSayi == 2) { renkLine = "blue"; renkDolgu = "blue"; }
                if (gSayi == 3) { renkLine = "green"; renkDolgu = "green"; }
                if (gSayi == 4) { renkLine = "red"; renkDolgu = "red"; }
                if (gSayi == 5) { renkLine = "orange"; renkDolgu = "orange"; }
                if (gSayi == 6) { renkLine = "orange"; renkDolgu = "yellow"; opacity = "0.60"; }
                if (gSayi == 7) { renkLine = "gray"; renkDolgu = "gray"; opacity = "0.35"; }
                if (gSayi == 8) { renkLine = "black"; renkDolgu = "gray"; opacity = "0.60"; }
                if (gSayi == 9) { renkLine = "#FF0066"; renkDolgu = "#FF0066"; opacity = "0.60"; } //pembe
                if (gSayi == 10) { renkLine = "blue"; renkDolgu = "blue"; }
                if (gSayi == 11) { renkLine = "green"; renkDolgu = "green"; }
                if (gSayi == 12) { renkLine = "red"; renkDolgu = "red"; }
                if (gSayi == 13) { renkLine = "orange"; renkDolgu = "orange"; }
                if (gSayi == 14) { renkLine = "orange"; renkDolgu = "yellow"; opacity = "0.60"; }
                if (gSayi == 15) { renkLine = "gray"; renkDolgu = "gray"; opacity = "0.35"; }



                kodPoligon = kodPoligon +
               "grupPoligon" + gSayi.ToString() + " = new google.maps.Polygon({\n" +
               "paths: grupPoligonCoords" + gSayi.ToString() + ",\n" +
               "strokeColor: '" + renkLine + "',\n" +
               "strokeOpacity: 0.8,\n" +
               "strokeWeight: 3,\n" +
               "fillColor: '" + renkDolgu + "',\n" +
               "fillOpacity: " + opacity + "\n" +
               "});\n" +
               "grupPoligon" + gSayi.ToString() + ".setMap(map);\n" +
               "attachPolygonInfoWindow(grupPoligon" + gSayi.ToString() + ", \" <strong>Group " + gSayi.ToString() + ": Click here to calculate distance to polygon! This process may take a few minutes. Please wait ...</string>\");\n" +
               "google.maps.event.addListener(grupPoligon" + gSayi.ToString() + ",'click',function(){\n" +
            "noktalar=grupPoligonCoords" + gSayi.ToString() + ";\n" +
            "for (var i = 0; i < noktalar.length; i++)\n " +
            "{\n" +
                "for (var j = 0; j < noktalar.length; j++) {\n" +
                "if(directionsDisplay != null) { " +
                    "directionsDisplay.setMap(null); " +
                   " directionsDisplay = null; " +
                  "  } " +
                  "directionsDisplay = new google.maps.DirectionsRenderer(rendererOptions);" +            
                "directionsDisplay.setMap(map);" +
                "directionsDisplay.setPanel(document.getElementById(\"directionsPanel\")); " +
                " if (i!=j){\n" +
                    "do{\n" +
                    "calcRoute(noktalar[i], noktalar[j]);\n" +
                    "sleep(1000);\n" + 
                    "}while(directionsDisplay.directions==null)\n" +                     
                    "myLabel=myLabel+\"(\"+i.toString()+\",\"+j.toString()+\")-->\"+computeTotalDistance(directionsDisplay.directions)+\"m\\n\";\n" + 
                    "kontrol=0;" +                                                     
                   " }\n" +
               " }\n" +
                "document.getElementById(\"ctl00_ContentPlaceHolder1_txtMesafe\").value = myLabel;\n" +           
           " }\n" +
       " });\n";
                
            }
            
            
            if (Satirlar[i].Trim() == "<group>")
            {
                gSayi++;
                elemanSira = 0;
               
            }            
            else 
            { 
              if (Satirlar[i].Trim() != "" && Satirlar[i].Trim() != "</group>" )
                {
                    elemanSira++;
                    kod = kod + "var coordinates = overlay.getProjection().fromContainerPixelToLatLng(new google.maps.Point("+ Satirlar[i] + "));\n";
                    kod = kod + "addPixelMarker(coordinates," + gSayi.ToString() + ");\n";
                    
                    if (elemanSira == 1) //grup başlangıç noktası
                    {
                        kodPoligon = kodPoligon + "var ilk" + gSayi.ToString() + " = overlay.getProjection().fromContainerPixelToLatLng(new google.maps.Point(" + Satirlar[i] + "));\n";
                        kodPoligon = kodPoligon +  "grupPoligonCoords" + gSayi.ToString() + ".push(ilk" + gSayi.ToString() + ");\n";
                        //YolTarif1 = YolTarif1 + "origin" + gSayi.ToString() + "= overlay.getProjection().fromContainerPixelToLatLng(new google.maps.Point(" + Satirlar[i] + "));\n";
                        
                    }
                    else
                    { 
                    kodPoligon = kodPoligon + "var coordinates" +gSayi.ToString()+" = overlay.getProjection().fromContainerPixelToLatLng(new google.maps.Point(" + Satirlar[i] + "));\n";
                    kodPoligon = kodPoligon + "grupPoligonCoords" + gSayi.ToString() + ".push(coordinates" + gSayi.ToString() + ");\n";
                    if (Satirlar[i + 1].Trim() != "</group>")
                    {
                        
                            //YolTarif1 = YolTarif1 + "var coordinates" + gSayi.ToString() + " = overlay.getProjection().fromContainerPixelToLatLng(new google.maps.Point(" + Satirlar[i] + "));\n";
                            //YolTarif1 = YolTarif1 + "waypoints" + gSayi.ToString() + ".push({location:coordinates" + gSayi.ToString() + ",stopover: true});\n";
                          
                        
                    }
                    }        
                }            
            }

        }
        Session["Parametreler"] = kod;
        Session["kodPoligon"] = kodPoligon;
        Session["YolTarif1"] = YolTarif1;
    }
}