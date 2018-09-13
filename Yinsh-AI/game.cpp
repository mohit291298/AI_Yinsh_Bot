#include <iostream>
#include <string>









TEMPLATE_ENVIRONMENT = Environment(
	autoescape=False,
	loader=FileSystemLoader(os.path.join(PATH, 'templates')),
	trim_blocks=False);

def render_template(template_filename, context):
	return TEMPLATE_ENVIRONMENT.get_template(template_filename).render(context)

void create_index_html(int size,int rings,int rows){
	string fname = "Yinsh.html";
	std::map <string, int> context;
	context['size'] = size;
	context['rings'] = rings;
	context['rows'] = rows;
	// context = {
	// 	'size': size,
	// 	'rings': rings,
	// 	'rows': rows
	// }
	FILE *f = fopen(fname, "w");
    if (f == NULL) {
        printf("Write error\n");
    } else {
        /* write n_students elements of the studentlist array */
        fwrite(studentlist, sizeof(student_t), n_students, f);
        fclose(f);
    }
	with open(fname, 'w') as f:
		html = render_template('index.html', context)
		f.write(html)
}


class Game{
public:
	int rings;
	int board_size;
	int display_size;
	float spacing;
	int centerx,centery;

	Game(int n,string mode,int time){
		if(n>=5 && n<=7){
			rings = n;
			board_size = board_sizes[n];
			display_size = display_sizes[n];
		}
		else{
			cout<<"Number of rings must be either 5, 6 or 7";
		}
		// create_index_html(display_size, n, board_size);
		// chrome_options = Options();
		// chrome_options.add_argument("--disable-infobars");
		// if (mode != "GUI"){
		// 	chrome_options.add_argument('headless');
		// }
		// self.driver = webdriver.Chrome(chrome_options=chrome_options)
		// string abs_path = os.path.abspath('Yinsh.html')
		// self.driver.get("file:" + abs_path)
		// self.driver.set_window_size(width=self.display_size, height=(self.display_size+60))

		spacing = float(self.display_size)/self.board_size;
		centerx = int(self.display_size)/2;
		centery = int(self.display_size)/2;

		//self.timer = time // Useful to optimise bot strategy

	}
		get_corner_coord(self, corner, hexagon) :
		x_mov = self.spacing * hexagon * math.sin(math.radians(corner * 60))
		y_mov = -(self.spacing * hexagon * math.cos(math.radians(corner * 60)))
		return np.array([self.centerx + x_mov, self.centery + y_mov])

	def get_non_corner_coord(self, corner1, corner2, point_num_side, hexagon) :
		corner1_coord = self.get_corner_coord(corner1, hexagon)
		corner2_coord = self.get_corner_coord(corner2, hexagon)
		return ((corner1_coord * (hexagon - point_num_side) / hexagon) + (corner2_coord * point_num_side / hexagon))

	def click_at(self, hexagon, point) :
		el = self.driver.find_elements_by_id("PieceLayer")
		action = webdriver.common.action_chains.ActionChains(self.driver)
		if (hexagon == 0) :
				action.move_to_element_with_offset(el[0], self.centerx, self.centery)
		else :
			if (point % hexagon == 0) :
				pt_coord = self.get_corner_coord(point / hexagon, hexagon)
				action.move_to_element_with_offset(el[0], pt_coord[0], pt_coord[1])
			else :
				pt_coord = self.get_non_corner_coord(point // hexagon, point // hexagon + 1, point % hexagon, hexagon)
				action.move_to_element_with_offset(el[0], pt_coord[0], pt_coord[1])
		action.click()
		action.perform()

}