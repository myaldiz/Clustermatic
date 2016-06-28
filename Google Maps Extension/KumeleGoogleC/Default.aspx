<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="_default" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Login</title>
</head>
<body style="background-color:#277acd;">
    <form id="form1" runat="server">
    <div style="width:602px;margin:60px auto auto auto;">
    <table id="Tablo_01" width="600px" height="400px" border="0" cellpadding="0" cellspacing="0">
	<tr>
		<td colspan="3">
			<img src="login/images/Login_01.png" width="600" height="267" alt=""></td>
	</tr>
	<tr>
		<td rowspan="6">
			<img src="login/images/Login_02.png" width="266" height="133" alt=""></td>
		<td width="161" height="24" style="padding-left:2px;background-image:url(login/images/Login_03.png)">
			<asp:TextBox ID="txtUserName" runat="server" BorderStyle="None" Width="154px" 
                style="background-color: #FFFFCC"></asp:TextBox>
			</td>
		<td rowspan="6">
			<img src="login/images/Login_04.png" width="173" height="133" alt=""></td>
	</tr>
	<tr>
		<td>
			<img src="login/images/Login_05.png" width="161" height="10" alt=""></td>
	</tr>
	<tr>
		<td width="161" height="24" style="padding-left:2px;background-image:url(login/images/Login_06.png)">
			<asp:TextBox ID="txtPassword" runat="server" BorderStyle="None" Width="154px" 
                style="background-color: #FFFFCC" TextMode="Password"></asp:TextBox>
			</td>
	</tr>
	<tr>
		<td>
			<img src="login/images/Login_07.png" width="161" height="9" alt=""></td>
	</tr>
	<tr>
		<td width="161" height="28" 
            style="background-image:url('login/images/Login_08.png'); text-align: right;">
			<asp:Button ID="btnLogin" runat="server" style="font-weight: 700" Text="Login" 
                Width="85px" onclick="btnLogin_Click1" />
			</td>
	</tr>
	<tr>
		<td>
			<img src="login/images/Login_09.png" width="161" height="38" alt=""></td>
	</tr>
    </table>
    </div>
    </form>
</body>
</html>
