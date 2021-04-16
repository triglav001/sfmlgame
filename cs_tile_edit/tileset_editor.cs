using System;
using System.IO;
using System.Drawing;
using System.Windows.Forms;
using System.Collections.Generic;
using System.Runtime.InteropServices;

[StructLayout(LayoutKind.Sequential, Pack=0)]
struct TileMapHeader
{
	public uint identifier;
	public ushort width;
	public ushort height;
	public uint tileset_id;
}

[StructLayout(LayoutKind.Sequential, Pack=0)]
struct Tile
{
	public ushort texture_id;
	public byte passable;
	public byte terrain_tag;
}

public class BorderPictureBox : PictureBox
{
	//public bool tile_passable = true;

	protected override void OnPaint(PaintEventArgs e) 
	{
		base.OnPaint(e);
		ControlPaint.DrawBorder(e.Graphics, e.ClipRectangle, this.ForeColor, ButtonBorderStyle.Solid);
	}
}

public class Globals
{
	public static uint t_width;
	public static uint t_height;
	public static string tileset_image_path = null;
	public static Bitmap tileset_bitmap;
	public static Bitmap[] tiles;
	public static uint img_cnt;


	public static Bitmap[] SplitBitmap (Bitmap image, int width, int height)
	{
	    int w = image.Width;
	    int h = image.Height;
	    if (w%width != 0 || h%height != 0)
	    {
	    	return null;
	    }
	    List<Bitmap> bmps = new List<Bitmap>();
	    w /= width;
	    h /= height;

	    RectangleF recf = RectangleF.Empty;//new RectangleF();

	    for (int i=0; i<h; i++)
	    {
	    	for (int j=0; j<w; j++)
	    	{
	    		recf = new RectangleF (j*width, i*height, width, height);
	    		bmps.Add(image.Clone(recf, image.PixelFormat));
	    	}
	    }

	    /*
	    //ImageList rows = new ImageList();
	    rows.ImageSize = new Size(image.Width, height);
	    rows.Images.AddStrip(image);
	    ImageList cells = new ImageList();
	    cells.ImageSize = new Size(width, height);
	    foreach (Image row in rows.Images)
	    {
	        cells.Images.AddStrip(row);
	    }
	    return cells;*/
	    return bmps.ToArray();
	}

	public static void ExportTileset (Panel p, string out_file)
	{
		TileMapHeader header;
		header.identifier = 1346456916;//BitConverter.ToInt32(byte[] {'T', 'M', 'A', 'P'});
		header.width = (ushort)t_width;
		header.height = (ushort)t_height;
		header.tileset_id = 0; // TODO

        Console.WriteLine("Exporting tileset ...");

		Tile[] tilez = new Tile[t_width * t_height];
		foreach (object o in p.Controls)
		{
			if (o is BorderPictureBox)
			{
				BorderPictureBox pb = o as BorderPictureBox;
				int y = pb.Top / 32;
				int x = pb.Left / 32;
				int id = (int)t_height * x + y;
                Console.WriteLine("Calculated ID: {0}", id);
                Console.WriteLine("From X:{0} Y:{1} and T_HEIGHT:{2}", x, y, t_height);
				tilez[id].passable = 1;
				if (pb.ForeColor == Color.Red) tilez[id].passable = 0;
				tilez[id].terrain_tag = 0; // TODO
				tilez[id].texture_id = 0;
				for (int i=0; i<tiles.Length; i++)
				{
                    Console.WriteLine("Adding {0}", i);
					if (pb.Image == tiles[i])
					{
						tilez[id].texture_id = (ushort)i;
						break;
					}
				}
				Console.WriteLine ("Added tile {0}", id);
			}
		}

		int size = Marshal.SizeOf(header);
	    byte[] arr = new byte[size];

	    IntPtr ptr = Marshal.AllocHGlobal(size);
	    Marshal.StructureToPtr(header, ptr, true);
	    Marshal.Copy(ptr, arr, 0, size);
	    Marshal.FreeHGlobal(ptr);

	    // Output
	    File.WriteAllBytes(out_file, arr);
	    Console.WriteLine("Written header: {0} bytes", size);

	    foreach (Tile t in tilez)
	    {
			size = Marshal.SizeOf(t);
		    arr = new byte[size];

		    ptr = Marshal.AllocHGlobal(size);
		    Marshal.StructureToPtr(t, ptr, true);
		    Marshal.Copy(ptr, arr, 0, size);
		    Marshal.FreeHGlobal(ptr);

		    // Output
		    Globals.AppendAllBytes(out_file, arr);
		    Console.WriteLine("Written tiles: {0} bytes", size);
	    }

	    Console.WriteLine("Finished!");

	}

	public static void AppendAllBytes(string path, byte[] bytes)
	{
	    //argument-checking here.

	    using (var stream = new FileStream(path, FileMode.Append))
	    {
	        stream.Write(bytes, 0, bytes.Length);
	    }
	}

}

public class TileSizeInputForm : Form
{
	private TextBox tb1;
	private TextBox tb2;

	private void ok_click (object sender, EventArgs e)
	{
		Globals.t_width = uint.Parse(tb1.Text);
		Globals.t_height = uint.Parse(tb2.Text);
		this.DialogResult = DialogResult.OK;
		this.Close();
	}

	public TileSizeInputForm()
	{
		Button ok_b = new Button();
		ok_b.Text = "OK";
		ok_b.Top = 200;
		ok_b.Left = 10;
		ok_b.Click += new EventHandler (ok_click);
		this.Controls.Add(ok_b);

		tb1 = new TextBox();
		tb1.Top = 10;
		tb1.Left = 10;
		this.Controls.Add(tb1);

		tb2 = new TextBox();
		tb2.Top = 100;
		tb2.Left = 10;
		this.Controls.Add(tb2);
	}
}

public class TileEditorForm : Form
{
	private Panel panel;
	private BorderPictureBox pb;
	private NumericUpDown num;
	private Color bef;

	private void click_pb (object sender, EventArgs e)
	{
		if (sender is BorderPictureBox)
		{
			BorderPictureBox p = sender as BorderPictureBox;
			p.Image = pb.Image;
			p.ForeColor = pb.ForeColor;
		}
		return;
	}

	private void click_main_pb (object sender, EventArgs e)
	{
		if (sender is BorderPictureBox)
		{
			BorderPictureBox p = sender as BorderPictureBox;
			//p.Image = pb.Image;
			if (p.ForeColor == Color.Red) p.ForeColor = bef;
			else p.ForeColor = Color.Red;//pb.ForeColor;
		}
		return;
	}

	private void new_tset_click (object sender, EventArgs e) 
	{
		Console.WriteLine ("Lojz.");
		TileSizeInputForm tsif = new TileSizeInputForm();
		tsif.ShowDialog();
		panel.Controls.Clear();
		for (int i=0; i<Globals.t_width; i++)
		{
			for (int j=0; j<Globals.t_height; j++)
			{
				BorderPictureBox pict = new BorderPictureBox();
				//pict.ForeColor = Color.Red;
				pict.Top = j*32;
				pict.Left = i*32;
				pict.Size = new Size(32, 32);
				pict.BorderStyle = BorderStyle.FixedSingle;
				pict.Click += new EventHandler(click_pb);
				panel.Controls.Add(pict);
			}
		}
		Console.WriteLine("Created new Tileset of size {0}x{1}", Globals.t_width, Globals.t_height);
	}

	private void changval (object sender, EventArgs e)
	{
		pb.Image = Globals.tiles[(int)num.Value];
	}

	private void save_tset_click (object sender, EventArgs e)
	{
		try 
		{
			SaveFileDialog ofd = new SaveFileDialog();
			ofd.Filter = "Tilemap (*.map)|*.map|All files (*.*)|*.*";
			//ofd.CheckFileExists = true;
			ofd.CheckPathExists = true;

			if (ofd.ShowDialog() != DialogResult.OK) return;
			Globals.ExportTileset(panel, ofd.FileName);
		}
		catch (Exception ex)
		{
			Console.WriteLine(ex.Message);
		}
	}

	private void load_img_click (object sender, EventArgs e)
	{
		try
		{
			OpenFileDialog ofd = new OpenFileDialog();
			ofd.Filter = "All files (*.*)|*.*";
			ofd.CheckFileExists = true;
			ofd.CheckPathExists = true;

			if (ofd.ShowDialog() != DialogResult.OK) return;
			Globals.tileset_image_path = ofd.FileName;
			Globals.tileset_bitmap = Bitmap.FromFile(Globals.tileset_image_path) as Bitmap;
			Globals.tiles = Globals.SplitBitmap(Globals.tileset_bitmap, 32, 32);
			Console.WriteLine("Loaded img {0}", Globals.tileset_image_path);
			Globals.img_cnt = 0;
			num.Enabled = true;
			num.Minimum = 0;
			num.Maximum = (Globals.tiles.Length - 1);
			num.ValueChanged += new EventHandler(changval);
			pb.Enabled = true;
			pb.Image = Globals.tiles[0];
		}
		catch (Exception ex)
		{
			Console.WriteLine(ex.Message);
		}
	}

    private void bclick (object o, EventArgs e)
    {
        var result = MessageBox.Show("Are you sure you want to fill an entire area?", "Fill area", MessageBoxButtons.YesNo);
        if (result == DialogResult.No)
        {
            return;
        }
        foreach (object obj in panel.Controls)
        {
            if (obj is BorderPictureBox)
            {
                BorderPictureBox bpb = obj as BorderPictureBox;
                bpb.Image = pb.Image;
                bpb.ForeColor = pb.ForeColor;
            }
        }
    }

	public TileEditorForm ()
	{
		panel = new Panel();
		panel.Top = 100;
		panel.Left = 10;
		MenuStrip ms = new MenuStrip();
		this.Controls.Add(ms);

		ToolStripMenuItem item = new ToolStripMenuItem("File");
		item.DropDownItems.Add("New Tileset");
		item.DropDownItems[0].Click += new EventHandler (new_tset_click);
		item.DropDownItems.Add("Load Tileset Image");
		item.DropDownItems[1].Click += new EventHandler (load_img_click);
		item.DropDownItems.Add("Save Tileset");
		item.DropDownItems[2].Click += new EventHandler (save_tset_click);
		ms.Items.Add(item);

		num = new NumericUpDown();
		num.Top = 30;
		num.Left = 10;
		num.Enabled = false;
		this.Controls.Add(num);

		pb = new BorderPictureBox();
		pb.Top = 30;
		pb.Left = 150;
		pb.BorderStyle = BorderStyle.FixedSingle;
		pb.Size = new Size(32, 32);
		pb.SizeMode = PictureBoxSizeMode.StretchImage;
		pb.Enabled = false;
		pb.Click += new EventHandler (click_main_pb);
		bef = pb.ForeColor;
		this.Controls.Add(pb);

        Button b = new Button();
        b.Text = "FILL";
        b.Top = 30;
        b.Left = 200;
        b.Click += new EventHandler(bclick);
        this.Controls.Add(b);

		panel.BorderStyle = BorderStyle.FixedSingle;
		panel.Size = new Size(800, 600);
		panel.AutoScroll = true;
		this.Controls.Add(panel);
	}
}

public class Program
{
	[STAThread]
	public static void Main ()
	{
		Application.EnableVisualStyles();
		Application.Run(new TileEditorForm ());
	}
}
