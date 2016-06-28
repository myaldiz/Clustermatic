using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class _default : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        txtUserName.Focus();
        btnLogin.Attributes.Add("id", "mehmet");
    }

    protected void btnLogin_Click1(object sender, EventArgs e)
    {
        if (txtUserName.Text.Trim() == "berk" && txtPassword.Text.Trim() == "berk")
        {
            Session["Login"] = "true";
            Response.Redirect("NoktalariBelirle.aspx");
        }
        else
        {
            RegisterStartupScript("startupScript", "<script language=JavaScript>alert('Wrong Username or Password! Please try again!');</script>");
        }
    }
}