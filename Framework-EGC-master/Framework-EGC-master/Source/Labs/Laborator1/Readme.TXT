Laborator 1 EGC - Florin Radulescu 333CC

Ex 2 -- obiect de tip Mesh ("teapot") incarcat in Laborator1::Init()
-- randare obiect nou in Laborator1::Update

Ex 3 -- includere variabile globale red, green , blue, setate initial pe 0
-- fiecare dintre ele are o tasta la apasarea careia valoarea trece pe 1
-- sau pe 0 (folosind proprietatile modulului) in Laborator1::OnKeyPress
-- se pot obtine combinatii ale culorilor pentru apasari diferite
-- (ex: rosu tasta F, verde tasta H, galben cand sunt ambele pe 1)

Ex 4 -- creare vector de nume in vector<string> objects; la apasarea unei
-- taste (B) in Laborator1::OnKeyPress se va incrementa/reseta indexul global
-- prin care se incarca obiectul in Laborator1::Update

Ex 5 -- obiectul de la Ex 4 este incarcat la pozitii reprezentate de variabile
-- globale pozX, pozY, pozZ; pe tot parcursul apasarii tatelor mentionate se va
-- misca in anumite directii (ex: A in sus, D in jos sau oblic la A + W/S)
-- actiunile sunt tratate cu window->KeyHold in Laborator1::OnInputUpdate si se 
-- produc doar daca nu se apasa mouseul pentru mutarea camerei
-- viteza de miscare creste/scade cu parametrul deltaTime


