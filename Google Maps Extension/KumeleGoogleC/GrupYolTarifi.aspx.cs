using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.IO;
using System.Text;
using System.Runtime.Serialization.Formatters.Binary;

public partial class GrupYolTarifi : System.Web.UI.Page
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
                YolTarif1 = YolTarif1 + "destination" + gSayi.ToString() + "= overlay.getProjection().fromContainerPixelToLatLng(new google.maps.Point(" + Satirlar[i - 1] + "));\n";

                //YolTarif1 = YolTarif1 + "destination" + gSayi.ToString() + "=origin" + gSayi.ToString()+"\n";
                YolTarif1 = YolTarif1 + "var mode;\n" +                
             "mode = google.maps.DirectionsTravelMode.DRIVING;\n" +
             " var request = {\n" +
              "origin: origin" + gSayi.ToString() + ",\n" +
              "destination: destination" + gSayi.ToString() + ",\n" +
             " waypoints: waypoints" + gSayi.ToString() + ",\n" +
             " travelMode: mode,\n" +
             " optimizeWaypoints: false,\n" +
              "avoidHighways: true,\n" +
             " avoidTolls: true\n" +
              "};\n" +
             " directionsService.route(request, function (response, status) {\n" +
             " if (status == google.maps.DirectionsStatus.OK) {\n" +
             "directionsDisplay.setOptions({polylineOptions: {\n" +
             "strokeColor: 'blue',strokeOpacity:0.55,strokeWeight:6\n" +
             "}});\n"+
              " directionsDisplay.setDirections(response);\n" +
              " mesafeYaz(response);}\n" +
              "});\n" +
              "//clearMarkers();\n" +
              "directionsVisible = true;\n" +         
              "}}\n";

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
               "grupPoligonCoords" + gSayi.ToString() + ".push(ilk" + gSayi.ToString() + ");\n" +
               "grupPoligon" + gSayi.ToString() + " = new google.maps.Polygon({\n" +
               "paths: grupPoligonCoords" + gSayi.ToString() + ",\n" +
               "strokeColor: '"+renkLine+"',\n" +
               "strokeOpacity: 0.8,\n" +
               "strokeWeight: 3,\n" +
               "fillColor: '"+renkDolgu+"',\n" +
               "fillOpacity: "+opacity+"\n" +
               "});\n" +
               "grupPoligon" + gSayi.ToString() + ".setMap(map);\n" +
               "attachPolygonInfoWindow(grupPoligon" + gSayi.ToString() + ", \" <strong>Group " + gSayi.ToString() + ": Click here for get directions</string>\");\n" +
               "google.maps.event.addListener(grupPoligon" + gSayi.ToString() + ", 'click', calcRoute" + gSayi.ToString() + ");\n";
            }
            
            
            if (Satirlar[i].Trim() == "<group>")
            {
                gSayi++;
                elemanSira = 0;
                YolTarif1 = YolTarif1 + "function calcRoute" + gSayi.ToString() + "() {\n";
                YolTarif1 = YolTarif1 + "if (grupPoligonCoords" + gSayi.ToString() + ".length>10){alert('You can get directions for maximum 10 points!');}else{\n";
                YolTarif1 = YolTarif1 + "grupPoligon" + gSayi.ToString() + ".setMap(null);\n";
                YolTarif1 = YolTarif1 + "clearMarkers();\n";                
                YolTarif1 = YolTarif1 + "map.setZoom(zoomLevel);\n map.setCenter(MapCenter);\n";
                YolTarif1 = YolTarif1 + "var overlay = new google.maps.OverlayView();\n" +
                                        "overlay.draw = function () { };\n" +
                                        "overlay.setMap(map);\n";
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
                        YolTarif1 = YolTarif1 + "origin" + gSayi.ToString() + "= overlay.getProjection().fromContainerPixelToLatLng(new google.maps.Point(" + Satirlar[i] + "));\n";
                        
                    }
                    else
                    { 
                    kodPoligon = kodPoligon + "var coordinates" +gSayi.ToString()+" = overlay.getProjection().fromContainerPixelToLatLng(new google.maps.Point(" + Satirlar[i] + "));\n";
                    kodPoligon = kodPoligon + "grupPoligonCoords" + gSayi.ToString() + ".push(coordinates" + gSayi.ToString() + ");\n";
                    if (Satirlar[i + 1].Trim() != "</group>")
                    {
                        
                            YolTarif1 = YolTarif1 + "var coordinates" + gSayi.ToString() + " = overlay.getProjection().fromContainerPixelToLatLng(new google.maps.Point(" + Satirlar[i] + "));\n";
                            YolTarif1 = YolTarif1 + "waypoints" + gSayi.ToString() + ".push({location:coordinates" + gSayi.ToString() + ",stopover: true});\n";
                          
                        
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