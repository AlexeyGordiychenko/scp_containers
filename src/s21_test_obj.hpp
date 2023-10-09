namespace s21 {
class test_obj {

private:
  static int ID;

public:
  int id;
  bool operator==(test_obj other) const { return id == other.id; }
  test_obj(/* args */);
  ~test_obj();
};

test_obj::test_obj(/* args */) : id(ID++) {}

test_obj::~test_obj() {}

int test_obj::ID = 0;
} // namespace s21