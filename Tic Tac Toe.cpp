#include<iostream>
#include<SFML/Graphics.hpp>
using namespace sf;
using namespace std;
const int SIZE = 3;
char board[SIZE][SIZE];
bool playerTurn = true;
void initBoard() {
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			board[i][j] = ' ';
}
//char checkWin() {
//	for (int i = 0; i < SIZE; i++) {
//		if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
//			return board[i][0];
//		if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
//			return board[0][i];
//	}
//	if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
//		return board[0][0];
//	if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
//		return board[0][2];
//	return ' ';
//}
//void drawBoard(RenderWindow& w1, Font& font) {
//	for (int i = 1;i < 4;i++) {
//		RectangleShape line(Vector2f(100.f, 80.f));
//		line.setFillColor(Color::White);
//		line.setPosition(i*100, 150);
//		line.setOutlineThickness(5.f);
//		line.setOutlineColor(Color::Black);
//		w1.draw(line);
//		line.setPosition(i*100,240);
//		w1.draw(line);
//		line.setPosition(i*100,330);
//		w1.draw(line);
//	}
//	for (int i = 0; i < SIZE; i++) {
//		for (int j = 0; j < SIZE; j++) {
//			if (board[i][j] != ' ') {
//				Text symbol(string(1, board[i][j]), font, 50);
//				symbol.setFillColor(Color::Black);
//				symbol.setPosition(j * 100 + 125, i * 100 + 160);
//				w1.draw(symbol);
//			}
//		}
//	}
//}
char checkWin() {
	for (int i = 0; i < SIZE; i++) {
		// Check rows and columns
		if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
			return board[i][0];
		if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
			return board[0][i];
	}
	// Check diagonals
	if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
		return board[0][0];
	if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
		return board[0][2];
	// Check if the board is full
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (board[i][j] == ' ') // Empty cell found
				return ' ';
		}
	}
	return 'D'; // Return 'D' for a draw
}
void drawBoard(RenderWindow& w1, Font& font) {
	for (int i = 1; i < SIZE; ++i) {
		RectangleShape verticalLine(Vector2f(5.f, 300.f));
		verticalLine.setFillColor(Color::Black);
		verticalLine.setPosition(i * 100 + 100, 150);
		w1.draw(verticalLine);
		RectangleShape horizontalLine(Vector2f(300.f, 5.f));
		horizontalLine.setFillColor(Color::Black);
		horizontalLine.setPosition(100, i * 100 + 150);
		w1.draw(horizontalLine);
	}
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (board[i][j] != ' ') {
				Text symbol(string(1, board[i][j]), font, 50);
				symbol.setFillColor(Color::Black);
				symbol.setPosition(j * 100 + 125, i * 100 + 160);
				w1.draw(symbol);
			}
		}
	}
}
void w2(Font& font) {
	RenderWindow w1(VideoMode(500.f, 600.f), "Tic Tac Toe Game");
	Text t("Player1(X) - Player2(O)", font, 45);
	t.setFillColor(Color::White);
	t.setPosition(Vector2f(15.f, 45.f));
	t.setOutlineThickness(5.f);
	t.setOutlineColor(Color::Black);
	RectangleShape box(Vector2f(170.f, 50.f));
	box.setFillColor(Color::Cyan);
	box.setPosition(Vector2f(170.f, 520.f));
	box.setOutlineThickness(5.f);
	box.setOutlineColor(Color::Black);
	Text r("Restart", font, 45);
	r.setFillColor(Color::Blue);
	r.setPosition(Vector2f(175.f, 520.f));
	r.setOutlineThickness(5.f);
	r.setOutlineColor(Color::Black);
	initBoard();
	while (w1.isOpen()) {
		Event event;
		while (w1.pollEvent(event)) {
			if (event.type == Event::Closed)
				w1.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				w1.close();
			// Handle resizing
			if (event.type == Event::Resized) {
				// Create a logical view (fixed coordinate system)
				View view(FloatRect(0, 0, 500, 600));  // Logical coordinate system: width=600, height=500
				w1.setView(view);
				// Adjust the view to match the new window size
				float aspectRatio = static_cast<float>(event.size.width) / event.size.height;
				view.setSize(500 * aspectRatio, 600);  // Adjust view size proportionally
				w1.setView(view);
			}
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
				Vector2f mousePosition = w1.mapPixelToCoords(Mouse::getPosition(w1));
				if (box.getGlobalBounds().contains(mousePosition)) {
					w1.close();
					w2(font);
				}
			}
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
				Vector2i mousePos = Mouse::getPosition(w1);
				int col = (mousePos.x - 100) / 100;
				int row = (mousePos.y - 150) / 100;
				if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ') {
					board[row][col] = playerTurn ? 'X' : 'O';
					playerTurn = !playerTurn;
				}
			}
		}
		w1.clear(Color::Blue);
		w1.draw(t);
		drawBoard(w1, font);
		char winner = checkWin();
		if (winner != ' ' && winner != 'D') {
			Text winText(string(1, winner) + " Wins! Congratulations", font, 43);
			winText.setFillColor(Color::White);
			winText.setPosition(Vector2f(20, 450));
			winText.setOutlineThickness(5.f);
			winText.setOutlineColor(Color::Red);
			w1.draw(winText);
		}
		else if (winner == 'D') {
			Text d("It's a DRAW",font,43);
			d.setFillColor(Color::White);
			d.setPosition(Vector2f(130, 450));
			d.setOutlineThickness(5.f);
			d.setOutlineColor(Color::Red);
			w1.draw(d);
		}
		w1.draw(box);
		w1.draw(r);
		w1.display();
	}
}
int main() {
	RenderWindow w1(VideoMode(700.f, 600.f), "Tic Tac Toe Game");
	Font font;
	if (!font.loadFromFile("arial.ttf")) {
		cout<<"Failed to load font!" << endl;
		return -1;
	}
	Text m("Tic Tac Toe Game", font, 45);
	m.setFillColor(Color::Magenta);
	m.setPosition(Vector2f(160.f, 150.f));
	m.setOutlineThickness(5.f);
	m.setOutlineColor(Color::Black);
	RectangleShape box(Vector2f(100.f, 50.f));
	box.setFillColor(Color::Cyan);
	box.setPosition(Vector2f(300.f, 251.f));
	box.setOutlineThickness(5.f);
	box.setOutlineColor(Color::Black);
	Text t("Play", font, 45);
	t.setFillColor(Color::Blue);
	t.setPosition(Vector2f(305.f, 245.f));
	t.setOutlineThickness(5.f);
	t.setOutlineColor(Color::Black);
	while (w1.isOpen()) {
		Event event;
		while (w1.pollEvent(event)) {
			if (event.type == Event::Closed)
				w1.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				w1.close();
			// Handle resizing
			if (event.type == Event::Resized) {
				// Create a logical view (fixed coordinate system)
				View view(FloatRect(0, 0, 700,600));  // Logical coordinate system: width=600, height=500
				w1.setView(view);
				// Adjust the view to match the new window size
				float aspectRatio = static_cast<float>(event.size.width) / event.size.height;
				view.setSize(700 * aspectRatio, 600);  // Adjust view size proportionally
				w1.setView(view);
			}
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
				Vector2f mousePosition = w1.mapPixelToCoords(Mouse::getPosition(w1));
				if (box.getGlobalBounds().contains(mousePosition)) {
					w1.close();
					w2(font);
				}
			}
		}
		w1.clear(Color::Green);
		w1.draw(m);
		w1.draw(box);
		w1.draw(t);
		w1.display();
	}
	return 0;
}
