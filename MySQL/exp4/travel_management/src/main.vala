// 2022 SuperBart, released under SuperBart Public Domain Software License.
// Database project, entry.

void main (string[] args)
{
    Travel_Management.Database toUse = new Travel_Management.Database ();
    Travel_Management.management_admin admin = new Travel_Management.management_admin (toUse);
    admin.management ();
	return;
}

