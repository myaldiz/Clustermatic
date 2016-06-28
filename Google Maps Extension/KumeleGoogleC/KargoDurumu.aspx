<%@ Page Title="" Language="C#" MasterPageFile="~/MasterPage.master" ValidateRequest="false" AutoEventWireup="true" CodeFile="KargoDurumu.aspx.cs" Inherits="KargoDurumu" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" Runat="Server">
    <style type="text/css">
     
      #latlng-control {
        background: #ffc;
        border: 1px solid #676767;
        font-family: arial, helvetica, sans-serif;
        font-size: 0.7em;
        padding: 2px 4px;
        position: absolute;
      }
    #txtSayi
    {
        width: 16px;
        height: 17px;
        background-color: #FFFFCC;
    }
        #Button1
        {
            font-weight: 700;
        }
        #Button2
        {
            width: 120px;
        }
        #btnPoligonOlustur
        {
            width: 130px;
        }
        #btnGrupGetir
        {
            width: 167px;
        }
        
    .style1
    {
        width: 39px;
    }
        
    </style>    

<script type="text/javascript" src="http://maps.google.com/maps/api/js?sensor=false&language=en"></script>
<script type="text/javascript">
 function sleep(milliseconds) {
        var start = new Date().getTime();
        while ((new Date().getTime() - start) < milliseconds) {
            // Do nothing
        }
    }   
    
    var directionDisplay;
    var directionsService = new google.maps.DirectionsService();
    var map;
//    var zoomLevel=14;
//    var MapCenter = new google.maps.LatLng(41.0283, 28.8498);
<%=Session["MapCenter"] %>
     //var ankara = new google.maps.LatLng(39.91996427368672, 32.85342008331304);
    var origin = null;
    var destination = null;
    var waypoints = [];

    var origin1 = null;
    var destination1 = null;
    var waypoints1 = [];

    var origin2 = null;
    var destination2 = null;
    var waypoints2 = [];

    var origin3 = null;
    var destination3 = null;
    var waypoints3 = [];

    var origin4 = null;
    var destination4 = null;
    var waypoints4 = [];

    var origin5 = null;
    var destination5 = null;
    var waypoints5 = [];
    
    var origin6 = null;
    var destination6 = null;
    var waypoints6 = [];
    
    var origin7 = null;
    var destination7 = null;
    var waypoints7 = [];

    var origin8 = null;
    var destination8 = null;
    var waypoints8 = [];

    var origin9 = null;
    var destination9 = null;
    var waypoints9 = [];
    
    var origin10 = null;
    var destination10 = null;
    var waypoints10 = [];
    
    var origin11 = null;
    var destination11 = null;
    var waypoints11 = [];
    
    var origin12 = null;
    var destination12 = null;
    var waypoints12 = [];
    
    var origin13 = null;
    var destination13 = null;
    var waypoints13 = [];

    var origin14 = null;
    var destination14 = null;
    var waypoints14 = [];

    var origin15 = null;
    var destination15 = null;
    var waypoints15 = [];


    var markers = [];
    var directionsVisible = false;

     var grupPoligon1;
        var grupPoligon2;
        var grupPoligon3;
        var grupPoligon4;
        var grupPoligon5;
        var grupPoligon6;
        var grupPoligon7;
        var grupPoligon8;
        var grupPoligon9;
        var grupPoligon10;
        var grupPoligon11;
        var grupPoligon12;
        var grupPoligon13;
        var grupPoligon14;
        var grupPoligon15;

    //var ankaraX = new google.maps.LatLng(39.91996427368672, 32.85342008331304);

    function LatLngControl(map) {
        /**
        * Offset the control container from the mouse by this amount.
        */
        this.ANCHOR_OFFSET_ = new google.maps.Point(8, 8);

        /**
        * Pointer to the HTML container.
        */
        this.node_ = this.createHtmlNode_();

        // Add control to the map. Position is irrelevant.
        map.controls[google.maps.ControlPosition.TOP].push(this.node_);

        // Bind this OverlayView to the map so we can access MapCanvasProjection
        // to convert LatLng to Point coordinates.
        this.setMap(map);

        // Register an MVC property to indicate whether this custom control
        // is visible or hidden. Initially hide control until mouse is over map.
        this.set('visible', false);
    }

    // Extend OverlayView so we can access MapCanvasProjection.
    LatLngControl.prototype = new google.maps.OverlayView();
    LatLngControl.prototype.draw = function () { };

    /**
    * @private
    * Helper function creates the HTML node which is the control container.
    * @return {HTMLDivElement}
    */
    LatLngControl.prototype.createHtmlNode_ = function () {
        var divNode = document.createElement('div');
        divNode.id = 'latlng-control';
        divNode.index = 100;
        return divNode;
    };

    /**
    * MVC property's state change handler function to show/hide the
    * control container.
    */
    LatLngControl.prototype.visible_changed = function () {
        this.node_.style.display = this.get('visible') ? '' : 'none';
    };

    /**
    * Specified LatLng value is used to calculate pixel coordinates and
    * update the control display. Container is also repositioned.
    * @param {google.maps.LatLng} latLng Position to display
    */
    LatLngControl.prototype.updatePosition = function (latLng) {
        var projection = this.getProjection();
        var point = projection.fromLatLngToContainerPixel(latLng);

        // Update control position to be anchored next to mouse position.
        this.node_.style.left = point.x + this.ANCHOR_OFFSET_.x + 'px';
        this.node_.style.top = point.y + this.ANCHOR_OFFSET_.y + 'px';

        // Update control to display latlng and coordinates.
        this.node_.innerHTML = [
          'LatLng..: ', latLng.toUrlValue(4),
         '<br/>Pixel....:',
          point.x.toFixed(0),
          'px, ',
          point.y.toFixed(0),
          'px'
        ].join('');
    };

    LatLngControl.prototype.Kaydet = function (latLng) {
        var projection = this.getProjection();
        var point = projection.fromLatLngToContainerPixel(latLng)
        document.getElementById("ctl00_ContentPlaceHolder1_txtKoordinat").value = document.getElementById("ctl00_ContentPlaceHolder1_txtKoordinat").value + point.x.toFixed(0) + "," + point.y.toFixed(0) + "\n";
        document.getElementById("txtSayi").value = markers.length + 1;
    }



    function initialize() {
        directionsDisplay = new google.maps.DirectionsRenderer();
       
        var myOptions = {
            zoom: zoomLevel,
            mapTypeId: google.maps.MapTypeId.ROADMAP,
            center: MapCenter
        }
        map = new google.maps.Map(document.getElementById("map_canvas"), myOptions);
        directionsDisplay.setMap(map);
        directionsDisplay.setPanel(document.getElementById("directionsPanel"));

        var latLngControl = new LatLngControl(map);
 
        google.maps.event.addListener(map, 'click', function (event) {});              
    
    }

       function grupOlustur()
        {        
        var overlay = new google.maps.OverlayView();
         overlay.draw = function () { };
         overlay.setMap(map);         
         <%=Session["parametreler"]%>                
        
        }

       function PoligonOlustur()
       {      
       var overlay = new google.maps.OverlayView();
         overlay.draw = function () { };
         overlay.setMap(map); 
        
       
        
        var grupPoligonCoords1=[];
        var grupPoligonCoords2=[];
        var grupPoligonCoords3=[];
        var grupPoligonCoords4=[];
        var grupPoligonCoords5=[];
        var grupPoligonCoords6=[];
        var grupPoligonCoords7=[];
        var grupPoligonCoords8=[];
        var grupPoligonCoords9=[];
        var grupPoligonCoords10=[];
        var grupPoligonCoords11=[];
        var grupPoligonCoords12=[];
        var grupPoligonCoords13=[];
        var grupPoligonCoords14=[];
        var grupPoligonCoords15=[];     
       
        <%=Session["kodPoligon"]%>
        

       }

    function addMarker(latlng,ico) {
        markers.push(new google.maps.Marker({
            position: latlng,
            map: map,
            //            icon: "http://maps.google.com/mapfiles/marker" + String.fromCharCode(markers.length + 65) + ".png"
            //            icon: "image\\ry" + (markers.length + 1) + ".png"                       
            icon: ico,
            animation: google.maps.Animation.DROP,
            title: "Sıra No: " + (markers.length + 1)
        }));
    }


    //*******************************************************************************
    function addPixelMarkerKargo(coord,res) {
        //var coord = new map.fromContainerPixelToLatLng(new GPoint(200, 200));
        var resim;
        var mesaj;
        if (res=="1") {resim="images\\cargo.png";mesaj="Waiting."}
        if (res=="2") {resim="images\\no.png";mesaj="Not found at home!"}
        if (res=="3") {resim="images\\ok.png";mesaj="Was delivered."}        

        markers.push(new google.maps.Marker({
            position: coord,
            map: map,
            //            icon: "http://maps.google.com/mapfiles/marker" + String.fromCharCode(markers.length + 65) + ".png"
            //            icon: "image\\ry" + (markers.length + 1) + ".png"
            icon: resim,
            animation: google.maps.Animation.DROP,
            title: mesaj
        }));
    }

    //*******************************************************************************

    function addPixelMarker(coord,res) {
        //var coord = new map.fromContainerPixelToLatLng(new GPoint(200, 200));
        var resim;
        if (res==1) {resim="images\\pemberaptiye.png"}
        if (res==2) {resim="images\\maviraptiye.png"}
        if (res==3) {resim="images\\yesilraptiye.png"}
        if (res==4) {resim="images\\kirmiziraptiye.png"}
        if (res==5) {resim="images\\turuncuraptiye.png"} 
        if (res==6) {resim="images\\sariraptiye.png"}               
        if (res==7) {resim="images\\siyahraptiye.png"}
        if (res==8) {resim="images\\beyazraptiye.png"}
        if (res==9) {resim="images\\pemberaptiye.png"}
        if (res==10) {resim="images\\maviraptiye.png"}
        if (res==11) {resim="images\\yesilraptiye.png"}
        if (res==12) {resim="images\\kirmiziraptiye.png"}
        if (res==13) {resim="images\\turuncuraptiye.png"} 
        if (res==14) {resim="images\\sariraptiye.png"}               
        if (res==15) {resim="images\\siyahraptiye.png"}

        markers.push(new google.maps.Marker({
            position: coord,
            map: map,
            //            icon: "http://maps.google.com/mapfiles/marker" + String.fromCharCode(markers.length + 65) + ".png"
            //            icon: "image\\ry" + (markers.length + 1) + ".png"
            icon: resim,
            animation: google.maps.Animation.DROP,
            title: "Sıra No: " + (markers.length + 1)
        }));
    }

  
        <%=Session["YolTarif1"]%>



  
    function clearMarkers() {
        for (var i = 0; i < markers.length; i++) {
            markers[i].setMap(null);
        }
    }

    function clearWaypoints() {
        //markers = [];
        origin1 = null;
        destination1 = null;
        waypoints1 = [];
         
        origin2 = null;
        destination2 = null;
        waypoints2 = [];
         
        origin3 = null;
        destination3 = null;
        waypoints3 = [];
         
        origin4 = null;
        destination4 = null;
        waypoints4 = [];
        
        origin5 = null;
        destination5 = null;
        waypoints5 = [];
        
        origin6 = null;
        destination6 = null;
        waypoints6 = [];
        
        origin7 = null;
        destination7 = null;
        waypoints7 = [];

        origin8= null;
        destination8 = null;
        waypoints8 = [];
        
        origin9= null;
        destination9 = null;
        waypoints9 = [];
        
        origin10= null;
        destination10 = null;
        waypoints10 = [];

        origin11= null;
        destination11 = null;
        waypoints11 = [];

        origin12= null;
        destination12 = null;
        waypoints12 = [];

        origin13= null;
        destination13 = null;
        waypoints13 = [];
        
        origin14= null;
        destination14 = null;
        waypoints14 = [];
        
        origin15= null;
        destination15 = null;
        waypoints15 = [];
        
        directionsVisible = false;
    }

    function reset() {
        //clearMarkers();
        clearWaypoints();
        directionsDisplay.setMap(null);
        directionsDisplay.setPanel(null);
        directionsDisplay = new google.maps.DirectionsRenderer();
        directionsDisplay.setMap(map);
        directionsDisplay.setPanel(document.getElementById("directionsPanel"));
    }
    
    
    function attachPolygonInfoWindow(polygon, html)
    {
        polygon.infoWindow = new google.maps.InfoWindow({
        content: html
        });
        google.maps.event.addListener(polygon, 'mouseover', function(e) {
        var latLng = e.latLng;
        this.setOptions({fillOpacity:0.35});
        polygon.infoWindow.setPosition(latLng);
        polygon.infoWindow.open(map);
        });
        google.maps.event.addListener(polygon, 'mouseout', function() {
        this.setOptions({fillOpacity:0.20});
        polygon.infoWindow.close();
        });
    }

    
    google.maps.event.addDomListener(window, 'load', initialize);    
</script>
    <asp:Literal ID="ltrParametreler" runat="server"></asp:Literal>
</asp:Content>
<asp:Content ID="Content3" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
    <div style="margin:0 auto 0 auto;position:relative; border: 1px; width:1100px; height: 600px;">
    <table>
    <tr>
    <td>
    <div id="map_canvas" style="border:1px solid dodgerblue;width:900px; height:600px">
    </div>
    </td>
    <td>
    <div id="KoordinatPanel" style="margin-left:1px;border:1px solid dodgerblue;text-align:center ;width:200px; height:600px; overflow: auto">
        <br />
        <br />
        <br />
        <input id="btnGrupGetir" type="button" value="Show Cargo Status" 
            
            onclick="javascript:grupOlustur();PoligonOlustur();document.getElementById('btnGrupGetir').disabled=false;" 
            style="font-weight: bold" /><br />
        <br />
        <strong>
        <br />
        <br />
        <br />
        Symbol meanings<br />
        </strong><br />
            <table style="text-align:center;font-family:verdana;vertical-align:middle;font-size:9pt; width: 180px;">
            <tr><td style="text-align:right; vertical-align:middle" class="style1"><img alt="" src="images/no.png" /></td>
                <td style="text-align: left"> Not found at home</td></tr>
            <tr><td style="text-align:right; vertical-align:middle" class="style1"><img alt="" src="images/ok.png" /> </td>
                <td style="text-align: left"> Was delivered</td></tr>
            <tr><td style="text-align:right; vertical-align:middle" class="style1"><img alt="" src="images/cargo.png"/> </td>
                <td style="text-align: left"> Waiting</td></tr>
            </table>        
        
        <br />
       
    </div>    
    </td>    
    </tr>    
    </table>
  </div>    
</asp:Content>
