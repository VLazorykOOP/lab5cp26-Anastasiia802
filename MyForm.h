#pragma once

#include <cmath>

namespace Lab5_Graphics {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			// Налаштування вікна
			this->Text = "Lab 5: Bezier & Sierpinski (Variant 8)";
			this->Size = System::Drawing::Size(800, 600);
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::Container^ components;

		// --- МЕТОДИ МАЛЮВАННЯ (Варіант 8) ---

		// Задача 1.2: Параметрична крива Безьє
		void DrawBezierCurve(Graphics^ g, Pen^ pen, PointF p1, PointF p2, PointF p3, PointF p4) {
			PointF prevPoint = p1;
			// t змінюється від 0 до 1 з кроком 0.005 для плавності
			for (float t = 0; t <= 1.0f; t += 0.005f) {
				float u = 1 - t;
				float tt = t * t;
				float uu = u * u;
				float uuu = uu * u;
				float ttt = tt * t;

				// Формула кубічної кривої Безьє
				float x = uuu * p1.X + 3 * uu * t * p2.X + 3 * u * tt * p3.X + ttt * p4.X;
				float y = uuu * p1.Y + 3 * uu * t * p2.Y + 3 * u * tt * p3.Y + ttt * p4.Y;

				PointF currPoint = PointF(x, y);
				g->DrawLine(pen, prevPoint, currPoint);
				prevPoint = currPoint;
			}
		}

		// Задача 2.8: Килим Серпінського
		void DrawSierpinskiCarpet(Graphics^ g, Brush^ brush, float x, float y, float w, float h, int k) {
			if (k == 0) {
				g->FillRectangle(brush, x, y, w, h);
				return;
			}

			float nw = w / 3.0f;
			float nh = h / 3.0f;

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					// Логіка: малюємо 8 квадратів, пропускаючи центральний?
					// Варіант 8 каже: "правило відносно кутових та центрального".
					// Класичний килим Серпінського - це дірка в центрі.
					// Але якщо треба малювати ТІЛЬКИ кутові та центр (хрест), умова змінюється.
					// Нижче реалізовано класичний килим (вирізаємо центр).
					// Якщо треба малювати тільки кути і центр (як "5 точок на кубику"), розкоментуйте іншу умову.

					// Класичний килим (вирізаємо центр):
					if (!(i == 1 && j == 1)) {
						DrawSierpinskiCarpet(g, brush, x + i * nw, y + j * nh, nw, nh, k - 1);
					}
				}
			}
		}

		void InitializeComponent(void)
		{
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
		}

		// Подія малювання
		System::Void MyForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
			Graphics^ g = e->Graphics;
			g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

			// --- 1. Малюємо криву Безьє ---
			Pen^ redPen = gcnew Pen(Color::Red, 2);
			PointF p1(50, 300);   // Початок
			PointF p2(150, 50);   // Керуюча точка 1 (верх)
			PointF p3(350, 50);   // Керуюча точка 2 (верх)
			PointF p4(450, 300);  // Кінець

			DrawBezierCurve(g, redPen, p1, p2, p3, p4);

			// Малюємо точки для наочності (сірі лінії)
			g->DrawLine(Pens::Gray, p1, p2);
			g->DrawLine(Pens::Gray, p3, p4);
			g->DrawString("Bezier Curve", this->Font, Brushes::Black, 200, 20);


			// --- 2. Малюємо Фрактал (Килим Серпінського) ---
			Brush^ blueBrush = Brushes::Blue;
			// Координати (x=500, y=50), Розмір (250x250), Глибина рекурсії (4)
			DrawSierpinskiCarpet(g, blueBrush, 500, 50, 250, 250, 4);
			g->DrawString("Sierpinski Carpet", this->Font, Brushes::Black, 550, 20);
		}
	};
}