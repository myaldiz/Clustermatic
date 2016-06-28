<%@ Page Title="" Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="kargoislem.aspx.cs" Inherits="kargoislem" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" Runat="Server">
    <style>
.secim
{
  
   border:0px;
   opacity:0.3;
   filter:alpha(opacity=30); /* For IE8 and earlier */
}    

.secim:hover
{
   
   border:0px;
   opacity:1.0;
   filter:alpha(opacity=100); /* For IE8 and earlier */
}
.durum
{
   border:0px solid white;
}    
        .style1
        {
            font-size: xx-small;
            color: #FF0000;
        }
        .style2
        {
            width: 157px;
        }
        .style3
        {
            width: 13px;
        }
        .style4
        {
            width: 79px;
        }
    </style>

</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
    <div style="margin:0 auto 0 auto;position:relative; border: 1px; width:450px; height: 600px;">
        Choose a group:
    <asp:DropDownList ID="drpGrup" runat="server" AutoPostBack="True" 
        onselectedindexchanged="drpGrup_SelectedIndexChanged" Width="210px" 
        Font-Bold="True">
    </asp:DropDownList>
    <br />
&nbsp;<asp:GridView ID="grdKargo" runat="server" 
    CellPadding="3" EnableModelValidation="True" 
    GridLines="Vertical" Width="431px" AutoGenerateColumns="False" 
        BackColor="White" BorderColor="#999999" BorderStyle="Solid" BorderWidth="1px" 
        DataKeyNames="MSatir" style="font-family: Arial; font-size: small" 
            Caption="&lt;b&gt;Cargo information for the selected group&lt;b/&gt;" 
            Height="226px">
    <AlternatingRowStyle BackColor="Gainsboro" />
        <Columns>
            <asp:BoundField DataField="MSira" HeaderText="Cargo&lt;br/&gt;Number" 
                HtmlEncode="False" >
            <ItemStyle Font-Bold="True" />
            </asp:BoundField>
            <asp:TemplateField HeaderText="Delivery&lt;br/&gt;Status">                
                <ItemTemplate>
                 <img class="durum" src="images/<%# Eval("Mislem") %>.png" />                   
                </ItemTemplate>
            </asp:TemplateField>
            <asp:BoundField DataField="Mkoord" HeaderText="Coordinates&lt;br/&gt;(Pixel)" 
                HtmlEncode="False" />
            <asp:TemplateField HeaderText="Changing&lt;br/&gt;the shipping status">                
                <ItemTemplate>
                    <a  href="kargoislem.aspx?satir=<%#Eval("MSatir")%>&islem=1"><img class="secim" src="images/1.png" title="Waiting"/></a>
                    <a href="kargoislem.aspx?satir=<%#Eval("MSatir")%>&islem=2"><img class="secim" src="images/2.png" title="Not found at home"/></a>
                    <a href="kargoislem.aspx?satir=<%#Eval("MSatir")%>&islem=3"><img class="secim" src="images/3.png" title="Was delivered"/></a>
                </ItemTemplate>
            </asp:TemplateField>
        </Columns>
    <FooterStyle BackColor="#CCCCCC" ForeColor="Black" />
    <HeaderStyle BackColor="#000084" Font-Bold="True" ForeColor="White" />
    <PagerStyle BackColor="#999999" ForeColor="Black" HorizontalAlign="Center" />
    <RowStyle BackColor="#EEEEEE" ForeColor="Black" />
    <SelectedRowStyle BackColor="#008A8C" Font-Bold="True" ForeColor="White" />
</asp:GridView>
        <span class="style1"><strong style="font-size: small">Click on the symbol on the 
        right-hand column to change<br />
        the status of the cargo.</strong></span><br /><br />
<table style="text-align:center;font-family:verdana;vertical-align:middle;font-size:9pt; width: 440px;">
            <tr><td style="text-align:right; vertical-align:middle"><img alt="" src="images/cargo.png"/> </td>
                <td style="text-align: left" class="style4"> Waiting</td>           
            <td style="text-align:right; vertical-align:middle"><img alt="" src="images/no.png" /></td>
                <td style="text-align: left" class="style2"> Not found at home</td>
            <td style="text-align:right; vertical-align:middle" class="style3"><img alt="" src="images/ok.png" /> </td>
                <td style="text-align: left"> Was delivered</td></tr> </table>
                
</div>      
</asp:Content>