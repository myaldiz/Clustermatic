<%@ Page Title="" Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="NoktalariBelirle.aspx.cs" Inherits="NoktalariBelirle" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" Runat="Server">
    <title>Noktaları Belirle</title>
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
        #Select1
        {
            width: 164px;
        }
    </style>    

<script type="text/javascript" src="http://maps.google.com/maps/api/js?sensor=false&language=en"></script>
<script type="text/javascript">

    var directionDisplay;
    var directionsService = new google.maps.DirectionsService();
    var map;
    var origin = null;
    var destination = null;
    var waypoints = [];
    var markers = [];    
   
    var directionsVisible = false;
   <%=Session["MapCenter"] %>
   function sleep(milliseconds) {
        var start = new Date().getTime();
        while ((new Date().getTime() - start) < milliseconds) {
            // Do nothing
        }
    }
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
          'LatLng..: ',latLng.toUrlValue(4),
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
        document.getElementById("txtSayi").value = markers.length+1;
    }
    
    function initialize() {
        directionsDisplay = new google.maps.DirectionsRenderer();
        //var ankara = new google.maps.LatLng(39.91996427368672, 32.85342008331304);
        var myOptions = {
            zoom: zoomLevel,
            mapTypeId: google.maps.MapTypeId.ROADMAP,
            center: MapCenter
        }
        map = new google.maps.Map(document.getElementById("map_canvas"), myOptions);
        directionsDisplay.setMap(map);
        directionsDisplay.setPanel(document.getElementById("directionsPanel"));


        var latLngControl = new LatLngControl(map);

        google.maps.event.addListener(map, 'rightclick', function (event) {
            if (document.getElementById("chkRight").checked == true) {
                latLngControl.Kaydet(event.latLng);                
                if (origin == null) {
                    origin = event.latLng;                    
                    addMarker(origin);
                } else if (destination == null) {
                    destination = event.latLng;

                    addMarker(destination);
                } else {
                    if (waypoints.length < 201) {
                        waypoints.push({ location: destination, stopover: true });
                        destination = event.latLng;
                        addMarker(destination);
                    } else {
                        alert("200 taneden fazla marker koyamazsınız");
                    }
                }
            }
        });

        google.maps.event.addListener(map, 'click', function (event) {
            if (document.getElementById("chkRight").checked == false) {
                latLngControl.Kaydet(event.latLng);
                if (origin == null) {
                    origin = event.latLng;
                    addMarker(origin);
                } else if (destination == null) {
                    destination = event.latLng;

                    addMarker(destination);
                } else {
                    if (waypoints.length < 201) {
                        waypoints.push({ location: destination, stopover: true });
                        destination = event.latLng;
                        addMarker(destination);
                    } else {
                        alert("200 taneden fazla marker koyamazsınız");
                    }
                }
            }
        });
        
        google.maps.event.addListener(map, 'tilesloaded', function() {
            document.getElementById("ctl00_ContentPlaceHolder1_txtZoom").value=map.getZoom();
            document.getElementById("ctl00_ContentPlaceHolder1_txtCenter").value=map.getCenter().toUrlValue(4);
          });
        
        google.maps.event.addListener(map, 'zoom_changed', function() {
            document.getElementById("ctl00_ContentPlaceHolder1_txtZoom").value=map.getZoom();
          });
          google.maps.event.addListener(map, 'center_changed', function() {
            document.getElementById("ctl00_ContentPlaceHolder1_txtCenter").value=map.getCenter().toUrlValue(4);
          });
           
        // Register event listeners
        google.maps.event.addListener(map, 'mouseover', function (mEvent) {
            latLngControl.set('visible', true);
        });
        google.maps.event.addListener(map, 'mouseout', function (mEvent) {
            latLngControl.set('visible', false);
        });
        google.maps.event.addListener(map, 'mousemove', function (mEvent) {
            latLngControl.updatePosition(mEvent.latLng);
        });
    }


    function addMarker(latlng) {
        markers.push(new google.maps.Marker({
            position: latlng,
            map: map,
            //            icon: "http://maps.google.com/mapfiles/marker" + String.fromCharCode(markers.length + 65) + ".png"
            //            icon: "image\\ry" + (markers.length + 1) + ".png"
            icon: "images\\pemberaptiye.png",
            animation: google.maps.Animation.DROP,
            title: "Sıra No: " + (markers.length + 1)
        }));
    }


    //*******************************************************************************

    //*******************************************************************************

    function addPixelMarker() {
        var coord = new map.fromContainerPixelToLatLng(new GPoint(200, 200));

        markers.push(new google.maps.Marker({
            position: coord,
            map: map,
            //            icon: "http://maps.google.com/mapfiles/marker" + String.fromCharCode(markers.length + 65) + ".png"
            //            icon: "image\\ry" + (markers.length + 1) + ".png"
            icon: "images\\pemberaptiye.png",
            animation: google.maps.Animation.DROP,
            title: "Sıra No: " + (markers.length + 1)
        }));
    }



    function updateMode() {
        if (directionsVisible) {
            calcRoute();
        }
    }

    function clearMarkers() {
        for (var i = 0; i < markers.length; i++) {
            markers[i].setMap(null);
        }
    }

    function clearWaypoints() {
        markers = [];
        origin = null;
        destination = null;
        waypoints = [];
        directionsVisible = false;
    }

    function reset() {
        //clearMarkers();
        //clearWaypoints();
        directionsDisplay.setMap(null);
        directionsDisplay.setPanel(null);
        directionsDisplay = new google.maps.DirectionsRenderer();
        directionsDisplay.setMap(map);
        directionsDisplay.setPanel(document.getElementById("directionsPanel"));
    }
    google.maps.event.addDomListener(window, 'load', initialize);
</script>
    <asp:Literal ID="ltrParametreler" runat="server"></asp:Literal>
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
    <div style="margin:0 auto 0 auto;position:relative; border: 1px; width:1100px; height: 600px;">
    <table>
    <tr>
    <td style="width: 902px">
    <div id="map_canvas" style="border:1px solid dodgerblue; width:900px; height:600px">
    </div>
    </td>
    <td>
    <div id="KoordinatPanel" style="margin-left:1px;border:1px solid dodgerblue;text-align:center ;width:200px; height:600px; overflow: auto">
        Zoom&nbsp; /&nbsp; Center<br />
        <asp:TextBox ID="txtZoom" runat="server" style="background-color: #FFFFCC; font-size: x-small; font-weight: 700;" 
            Width="25px"></asp:TextBox>
        /<asp:TextBox ID="txtCenter" runat="server" style="background-color: #FFFFCC; font-size: x-small; font-weight: 700;" 
            Width="95px"></asp:TextBox>
        <asp:Button ID="btnMapKaydet" runat="server" Text="Save" 
            onclick="btnMapKaydet_Click" 
            style="font-size: x-small; font-weight: 700" />
        <br />
&nbsp; Coordinates (Count:<input id="txtSayi" type="text" />)
    <asp:TextBox ID="txtKoordinat" runat="server" Height="471px" TextMode="MultiLine" 
        Width="181px" style="background-color: #FFFFCC" Font-Names="Arial" 
            Font-Size="9pt"></asp:TextBox>
        <br />
        <asp:Button ID="Button1" runat="server" onclick="Button1_Click" 
            style="font-weight: 700" Text="Save Coordinates" Width="170px" />
        <br />
        Select Right Click:<input id="chkRight" type="checkbox" checked="checked"/></div>            
    </td>    
    </tr>    
    </table>
    
       
  </div>    
</asp:Content>

