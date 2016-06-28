<%@ Page Title="" Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="GrupKoordinatAktar.aspx.cs" Inherits="GrupKoordinatAktar" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" Runat="Server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
    <br />
    <br />
    <br />
    <br />
    <br />
    <span id="result_box" class="short_text" lang="en"><span class="hps">Choose 
a group file</span></span>:
    <asp:FileUpload ID="DosyaGonder" runat="server" Width="268px" />
    &nbsp;<asp:Button ID="btnGonder" runat="server" Text="Upload" Width="75px" 
        onclick="btnGonder_Click" style="font-weight: 700" />
    <br />
    <br />
    <br />
    <br />
    <br />
    <br />
    <br />
    <br />
    <br />
    <br />
    <br />
    <br />
    <br />
    <br />
    <br />
    <br />
</asp:Content>

