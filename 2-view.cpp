#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE); // close program on ESC key
}

void setup_viewport(GLFWwindow* window)
{
	// setting viewports size, projection etc
	float ratio;
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;
	glViewport(0, 0, width, height);

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-17, 17, -17, 17, 1.f, -1.f); // bisa diubah 17 dan -17 nya
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void grid(int baris, int kolom)
{
	int i;

	int kiri = -kolom / 2; //batas kiri x
	int kanan = kolom / 2; //batas kanan x
	int bawah = -baris / 2; //batas bawah y
	int atas = baris / 2; //batas atas y

	glBegin(GL_LINES);
	glLineWidth(1);
	//Baris digambar dari atas ke bawah
	for (i = 0; i < baris + 1; i++)
	{
		glVertex2f(kiri, baris / 2 - i);
		glVertex2f(kanan, baris / 2 - i);
	}

	//Kolom digambar dari kanan ke kiri
	for (i = 0; i < kolom + 1; i++)
	{
		glVertex2f(kolom / 2 - i, bawah);
		glVertex2f(kolom / 2 - i, atas);
	}

	glLineWidth(3);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(kiri, 0);
	glVertex2f(kanan, 0);
	glVertex2f(0, bawah);
	glVertex2f(0, atas);

	glEnd();
}

//gambar kotak
void rectangle(float horizontal, float vertical)
{
	horizontal /= 2;
	vertical /= 2;
	glBegin(GL_POLYGON);
	glVertex2f(-horizontal, vertical);
	glVertex2f(-horizontal, -vertical);
	glVertex2f(horizontal, -vertical);
	glVertex2f(horizontal, vertical);
	glEnd();
}

//gambar bundar
void lingkaran(float radius, int a) {
	glBegin(GL_POLYGON);

	int jumlah_titik = 360;
	int x_tengah = 0;
	int y_tengah = 0;
	int sudut, i;

	glVertex2f(x_tengah, y_tengah);

	for (i = 0; i <= a; i++) {
		float sudut = i * (2 * 3.14 / jumlah_titik);
		float x = x_tengah + radius * cos(sudut);
		float y = y_tengah + radius * sin(sudut);
		glVertex2f(x, y);

	}
	glVertex2f(x_tengah, y_tengah);
	glEnd();
}


void segitiga(float alas, float tinggi) {
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.5 * alas, 0);
	glVertex2f(0, tinggi);
	glVertex2f(0.5 * alas, 0);
	glEnd();
}

void jajargenjang(float horizontal, float vertical, float miring)
{
	horizontal /= 2;
	vertical /= 2;
	glBegin(GL_POLYGON);
	glVertex2f(-horizontal, vertical);
	glVertex2f(-horizontal, -vertical - miring);
	glVertex2f(horizontal, -vertical);
	glVertex2f(horizontal, vertical + miring);
	glEnd();
}

void jajargenjang_teras(float horizontal, float vertical, float miring)
{
	horizontal /= 2;
	vertical /= 2;
	glBegin(GL_POLYGON);
	glVertex2f(-horizontal, vertical);
	glVertex2f(-horizontal - miring, -vertical);
	glVertex2f(horizontal, -vertical);
	glVertex2f(horizontal + miring, vertical);
	glEnd();
}

void trapesium(float horizontal, float vertical, float miring)
{
	horizontal /= 2;
	vertical /= 2;
	glBegin(GL_POLYGON);
	glVertex2f(-horizontal - miring, vertical);
	glVertex2f(-horizontal, -vertical - miring);
	glVertex2f(horizontal + miring, -vertical);
	glVertex2f(horizontal, vertical + miring);
	glEnd();
}

void display()
{
	//bacground langit
	glColor3ub(135, 206, 250);
	rectangle(80, 80);

	//baground rumput hijau
	glTranslatef(0, -10, 0);
	glColor3ub(0, 170, 20);
	rectangle(40, 16);

	//matahari
	glTranslatef(-12, 20, 0);
	glColor3ub(255, 255, 0);
	lingkaran(1.3, 360);

	//gunung kanan
	glTranslatef(21, -12, 0);
	glColor3ub(150, 75, 0);
	segitiga(17, 10);

	//gunung kiri
	glTranslatef(-17, 0, 0);
	glColor3ub(150, 75, 0);
	segitiga(19, 10);

	//daun pohon
	glTranslatef(-4, -2, 0);
	glColor3ub(0, 104, 0);
	segitiga(5.5, 4);

	glTranslatef(-0, -1.5, 0);
	glColor3ub(0, 104, 0);
	segitiga(7, 4);

	glTranslatef(-0, -1.5, 0);
	glColor3ub(0, 104, 0);
	segitiga(7, 4);

	//batang pohon
	glTranslatef(0, -2, 0);
	glColor3ub(150, 75, 4);
	rectangle(1, 4);

	//------ rumah ------
	glTranslatef(18, 2.3, 0); //dinding miring bawah
	glColor3ub(230, 215, 89);
	jajargenjang(5, 1.2, 3);

	glTranslatef(-1.5, 3.1, 0); //atap merah
	glColor3ub(160, 35, 0);
	trapesium(2.9, 1.2, 3);

	glTranslatef(-4.3, -4.6, 0); //tembok
	glColor3ub(240, 230, 140);
	rectangle(7, 4);

	glTranslatef(0, -0.7, 0); //pintu
	glColor3ub(180, 35, 2);
	rectangle(4, 2.5);

	glTranslatef(0, 2.1, 0); //segitiga
	glColor3ub(180, 35, 2);
	segitiga(8, 4);

	glTranslatef(0, 3, 0); //tembok depan atas
	glColor3ub(240, 230, 140);
	rectangle(5, 3);

	glTranslatef(0, 0, 0); //pintu
	glColor3ub(180, 35, 2);
	rectangle(3, 0.8);

	glTranslatef(5.0, 1.6, 0); //dinding miring atas
	glColor3ub(230, 215, 89);
	jajargenjang(5, 0.2, 3);

	glTranslatef(-5.1, 0, 0); //pembatas teras
	glColor3ub(180, 35, 2);
	rectangle(4.8, 0.5);

	glTranslatef(5.1, 3, 0); //pembatas teras
	glColor3ub(180, 35, 2);
	rectangle(4.8, 0.5);

	glTranslatef(-0.1, -1.5, 0); //pembatas
	glColor3ub(180, 35, 2);
	jajargenjang(5.2, -2.4, 3);

	glTranslatef(-4.8, 0.0, 0); //pembatas
	glColor3ub(180, 35, 2);
	jajargenjang(5.2, -2.4, 3);

	glTranslatef(2.3, 0, 0); //teras abu-abu
	glColor3ub(128, 128, 128);
	jajargenjang_teras(-0.3, 2.5, 4.3);

	//awan
	glTranslatef(6, 12, 0);
	glColor3ub(122, 122, 122);
	lingkaran(1.3, 360);
	glTranslatef(1.5, 0.5, 0);
	glColor3ub(122, 122, 122);
	lingkaran(1.3, 360);
	glTranslatef(1.5, 0, 0);
	glColor3ub(122, 122, 122);
	lingkaran(1.3, 360);
	glTranslatef(1.5, -0.5, 0);
	glColor3ub(122, 122, 122);
	lingkaran(1.3, 360);
	glTranslatef(-1.5, -0.5, 0);
	glColor3ub(122, 122, 122);
	lingkaran(1.3, 360);
	glTranslatef(-1.5, 0, 0);
	glColor3ub(122, 122, 122);
	lingkaran(1.3, 360);

	glPushMatrix();
	glColor3ub(120, 255, 20);
	glTranslatef(0, 6, 0);
	glPopMatrix();
}



int main(void) {
	GLFWwindow* window;
	if (!glfwInit()) exit(EXIT_FAILURE);

	window = glfwCreateWindow(800, 600, "Pemandangan & Rumah", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}


	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(window, key_callback);


	//

	//Enable Alpha
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,
		GL_ONE_MINUS_SRC_ALPHA);

	//Enable Antialiasing
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_POINT_SMOOTH);

	while (!glfwWindowShouldClose(window))
	{
		setup_viewport(window);


		display();


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}