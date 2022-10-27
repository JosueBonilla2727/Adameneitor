#include<conio.h>
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

using namespace std;

class Node{
	public:
		Node* arbol = NULL;
		Node* der = nullptr;
		Node* izq = nullptr;
		Node* raiz = nullptr;

		string dato;
		int opz, contador =0;

	public:

		~Node() {
			delete der;
			delete izq;
			delete raiz;
		}
};

void mostrar_arbol(Node* arbol, int cont) {
	if (arbol == NULL) {
		return;
	}
	else {
		mostrar_arbol(arbol->der, cont + 1);
		for (int i = 0; i < cont; i++) {
			cout << "   ";
		}
		cout << arbol->dato << endl;
		mostrar_arbol(arbol->izq, cont + 1);
	}
}

Node* crearNodo(string n, Node* arbol) {
	Node* nuevo_nodo = new Node();
	nuevo_nodo->dato = n;
	nuevo_nodo->der = NULL;
	nuevo_nodo->izq = NULL;
	nuevo_nodo->raiz = *&arbol->raiz;
	return nuevo_nodo;
}

class Ventana2{
	public:
		sf::RenderWindow* renderwindow;

		sf::Event eventos;

		sf::ContextSettings conf;

		sf::Texture txt_fondo2;
		sf::Sprite spr_fondo2;

		sf::Texture txt_adame;
		sf::Sprite spr_adame;

		sf::RectangleShape* rectangulo_no;
		sf::RectangleShape* rectangulo_si;
		sf::RectangleShape* rectangulo_rein;

		sf::Text* txt_si;
		sf::Text* txt_no;
		sf::Text* txt_prg;
		sf::Text* txt_per;
		sf::Text* txt_rein;

		sf::Font fuente1;

		Node* arbol;
		char per[100], pre[100];
		int opt, gameover, scl;

		static Ventana2& instance() {
			static Ventana2 *instance = new Ventana2();
			return *instance;
		}

	public:

		Ventana2() {
			arbol = NULL;
			pre[50] = {}, per[50] = {};
			opt = 0, scl = 0, gameover = 0;

			crearVentana();
			crearRectangulos();
			craerFuente();
			cargarGraficos();

			mostrarVentana(NULL, 1);
		}

		void crearVentana() {
			conf.antialiasingLevel = 10;
			renderwindow = new sf::RenderWindow(sf::VideoMode(1000, 600), "ADAMENEITOR", sf::Style::Default, conf);
			renderwindow->setVerticalSyncEnabled(true);
		}

		void crearRectangulos() {
			rectangulo_no = new sf::RectangleShape(sf::Vector2f(200.f, 80.f));
			rectangulo_no->setFillColor(sf::Color::White);
			rectangulo_no->setPosition(545, 225);

			rectangulo_si = new sf::RectangleShape(sf::Vector2f(200.f, 80.f));
			rectangulo_si->setFillColor(sf::Color::White);
			rectangulo_si->setPosition(245, 225);

			rectangulo_rein = new sf::RectangleShape(sf::Vector2f(200.f, 80.f));
			rectangulo_rein->setFillColor(sf::Color::White);
			rectangulo_rein->setPosition(800, 500);
		}

		void craerFuente() {
			fuente1.loadFromFile("MINECRAFT.ttf");

			txt_si = new sf::Text();
			txt_si->setFont(fuente1);
			txt_si->setString("SI");
			txt_si->setPosition(235, 230);
			txt_si->setCharacterSize(24);
			txt_si->setFillColor(sf::Color::Red);
			txt_si->setStyle(sf::Text::Bold);

			txt_no = new sf::Text();
			txt_no->setFont(fuente1);
			txt_no->setString("NO");
			txt_no->setPosition(545, 230);
			txt_no->setCharacterSize(24);
			txt_no->setFillColor(sf::Color::Red);
			txt_no->setStyle(sf::Text::Bold);

			txt_rein = new sf::Text();
			txt_rein->setFont(fuente1);
			txt_rein->setString("REINICIAR");
			txt_rein->setPosition(805, 505);
			txt_rein->setCharacterSize(24);
			txt_rein->setFillColor(sf::Color::Red);
			txt_rein->setStyle(sf::Text::Bold );

		}

		void cargarGraficos() {
			txt_fondo2.loadFromFile("televisa.jpg");
			spr_fondo2.setTexture(txt_fondo2);
			spr_fondo2.setScale((float)renderwindow->getSize().x / txt_fondo2.getSize().x, (float)renderwindow->getSize().y / txt_fondo2.getSize().y);
		}

		void dibujarGraficos() {

			renderwindow->draw(spr_fondo2);
			renderwindow->draw(spr_adame);
			renderwindow->draw(*rectangulo_si);
			renderwindow->draw(*rectangulo_no);
			renderwindow->draw(*rectangulo_rein);
			renderwindow->draw(*txt_si);
			renderwindow->draw(*txt_no);
			renderwindow->draw(*txt_prg);
			renderwindow->draw(*txt_per);
			renderwindow->display();
		}

		void mostrarVentana(Node *arbol, int cont) {
			if (arbol == NULL) {
				Node* nodo_raiz = new Node();
				nodo_raiz->dato = "Es_real";
				nodo_raiz->der = NULL;
				nodo_raiz->izq = NULL;
				arbol = nodo_raiz;
				nodo_raiz->raiz = *&arbol;
				arbol = nodo_raiz;
			}
			string n_per = to_string(cont);
			txt_prg = new sf::Text(n_per, fuente1, 33);
			txt_prg->setPosition(180, 150);
			txt_prg->setFillColor(sf::Color::Black);

			txt_per = new sf::Text(arbol->dato, fuente1, 33);
			txt_per->setPosition(42, 150);
			txt_per->setFillColor(sf::Color::Black);

			while (renderwindow->isOpen()) {
				scl = 0;
				opt = 0;

				if (gameover == 1) {
					txt_adame.loadFromFile("adame2.png");
					spr_adame.setTexture(txt_adame);
					spr_adame.setPosition(300, 300);
				}
				else if (gameover == 2) {
					txt_adame.loadFromFile("adame3.png");
					spr_adame.setTexture(txt_adame);
					spr_adame.setPosition(300, 300);
				}
				else if (arbol->der == NULL && arbol->izq == NULL) {
					txt_adame.loadFromFile("adame1.png");
					spr_adame.setTexture(txt_adame);
					spr_adame.setPosition(300, 300);
				}
				else {
					txt_adame.loadFromFile("adame4.png");
					spr_adame.setTexture(txt_adame);
					spr_adame.setPosition(300, 300);
				}

				dibujarGraficos();

				if (gameover == 1) {
					gameover = 0;
					mostrarVentana(*&arbol->raiz, 1);
				}
				else if (gameover == 2) {
					gameover = 0;
					cout << "\nTu personaje es:" << std::endl;
					fflush(stdin);
					cin.getline(pre, 100);
					cout << "Personaje:" << std::endl;
					fflush(stdin);
					cin.getline(per, 100);

					Node* nodo_izq = crearNodo(arbol->dato, *&arbol->raiz);
					arbol->izq = nodo_izq;
					*&arbol->dato = pre;

					Node* nodo_der = crearNodo(per, *&arbol->raiz);
					arbol->der = nodo_der;

					mostrarVentana(*&arbol->raiz, 1);
				}

				while (renderwindow->pollEvent(eventos)) {
					switch (eventos.type)
					{
						case sf::Event::Closed:
							renderwindow->close();
							break;
						case sf::Event::MouseMoved:
						{
							sf::Vector2i mousePos = sf::Mouse::getPosition(*renderwindow);
							sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
							if (rectangulo_si->getGlobalBounds().contains(mousePosF))
							{
								rectangulo_si->setFillColor(sf::Color::Yellow);
							}
							else
							{
								rectangulo_si->setFillColor(sf::Color::Blue);
							}
							if (rectangulo_no->getGlobalBounds().contains(mousePosF))
							{
								rectangulo_no->setFillColor(sf::Color::Yellow);
							}
							else
							{
								rectangulo_no->setFillColor(sf::Color::Blue);
							}
						}
					}
					if (eventos.type == sf::Event::MouseButtonReleased) {
						if (eventos.mouseButton.button == sf::Mouse::Left) {
							if (rectangulo_si->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*renderwindow)))) {
								if (arbol->der == NULL && arbol->izq == NULL) {
									gameover = 1;
								}
								else {
									mostrarVentana(arbol->der, cont + 1);
								}
							}
							else if (rectangulo_no->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*renderwindow)))) {
								if (arbol->der == NULL && arbol->izq == NULL) {
									gameover = 2;
								}
								else {
									mostrarVentana(arbol->izq, cont + 1);
								}
							}
							else if (rectangulo_rein->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*renderwindow)))) {
								mostrarVentana(*&arbol->raiz, 1);
							}
						}
					}
					if (eventos.type == sf::Event::Closed) {
						renderwindow->close();
					}
				}
			}
		}

		~Ventana2() {
			delete renderwindow;
		}
};

void main() {
	system("cls");
	Ventana2::instance();
}


