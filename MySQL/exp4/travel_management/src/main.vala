
using GLib;

void main (string[] args)
{
    Travel_Management.Database toUse = new Travel_Management.Database ();
    Travel_Management.management_admin admin = new Travel_Management.management_admin (toUse);
    admin.management ();
	return;
}

