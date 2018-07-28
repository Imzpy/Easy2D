#pragma once
#include "e2dmacros.h"

namespace e2d
{


// ����
enum class Direction : int
{
	Up,			/* �� */
	Down,		/* �� */
	Left,		/* �� */
	Right		/* �� */
};


// �����ཻ��ʽ
enum class LineJoin : int
{
	Miter = 0,	/* б�� */
	Bevel = 1,	/* б�� */
	Round = 2	/* Բ�� */
};


class Size;

// ����
class Point
{
public:
	float x;	// X ����
	float y;	// Y ����

public:
	Point();

	Point(float x, float y);

	Point(const Point& other);

	Point operator + (Point const & point) const;
	Point operator - (Point const & point) const;
	Point operator * (float const & point) const;
	Point operator / (float const & point) const;
	Point operator - () const;
	bool operator== (const Point& point) const;

	operator e2d::Size() const;

	// �ж���������
	static float distance(const Point&, const Point&);
};


// ��ά����
typedef Point Vector2;


// ��С
class Size
{
public:
	float width;	// ���
	float height;	// �߶�

public:
	Size();

	Size(float width, float height);

	Size(const Size& other);

	Size operator + (Size const & size) const;
	Size operator - (Size const & size) const;
	Size operator * (float const & size) const;
	Size operator / (float const & size) const;
	Size operator - () const;
	bool operator== (const Size& size) const;

	operator e2d::Point() const;
};


// ����
class Rect
{
public:
	Point origin;	// ԭ������
	Size  size;		// ��Ⱥ͸߶�

public:
	Rect();
	
	Rect(float x, float y, float width, float height);
	
	Rect(const Point& pos, const Size& size);
	
	Rect(const Rect& other);
	
	Rect& operator= (const Rect& other);

	bool operator== (const Rect& rect) const;
	
	// ���þ���
	void setRect(
		float x, 
		float y, 
		float width, 
		float height
	);
	
	// �жϵ��Ƿ��ھ�����
	bool containsPoint(
		const Point& point
	) const;
	
	// �ж��������Ƿ��ཻ
	bool intersects(
		const Rect& rect
	) const;
};


// �ַ���
class String
{
public:
	String();
	String(const String &);
	String(const char *);
	String(const wchar_t *);
	String(String &&);

	~String();

	// �ж��ַ����Ƿ�Ϊ��
	bool isEmpty() const;

	// ��ȡ�ַ�������
	int getLength() const;

	// ��ȡ���ַ�����ɢ��ֵ
	size_t getHashCode() const;

	// ��ȡ Unicode �ַ���
	std::wstring getWString() const;

	// ��ȡ ANSI �ַ���
	std::string getCString() const;

	// ��ȡָ��λ���ַ�
	wchar_t at(
		int index
	) const;

	// �Ƚ��ַ���
	int compare(
		const String & str
	) const;

	// ��ȡ�ַ���
	e2d::String subtract(
		int offset,		/* ƫ���� */
		int count = -1	/* ��ȡ�ַ����� */
	) const;

	// �����ַ���
	void insert(
		const String & str,
		int pos
	);

	// �滻�ַ����е�ָ������
	void replace(
		const String & from,	/* ���滻���� */
		const String & to		/* �滻������ */
	);

	// ɾ���ַ����е�ָ������
	void erase(
		int offset,		/* ƫ���� */
		int count		/* ɾ���ַ����� */
	);

	// �����ַ���
	int find(
		const String & str,	/* �������� */
		int offset = 0		/* ƫ���� */
	) const;

	// ����ַ���
	void clear();

	// ��ȡ��д�ַ���
	String toUpper() const;

	// ��ȡСд�ַ���
	String toLower() const;

	// ���ַ���ת��Ϊ int ��
	int toInt() const;

	// ���ַ���ת��Ϊ float ��
	float toFloat() const;

	// ���ַ���ת��Ϊ double ��
	double toDouble() const;

	// ���ַ���ת��Ϊ bool ��
	bool toBool() const;

	// ��������ת�ַ���
	static String parse(int value);
	static String parse(unsigned int value);
	static String parse(float value);
	static String parse(double value);

	// ��ʽ���ַ���
	static String format(const char * format, ...);
	static String format(const wchar_t * format, ...);

	// �������ַ���
	static void swap(String &str1, String &str2);

	// ��ֵ�����
	String& operator= (const String &);
	String& operator= (const char *);
	String& operator= (const wchar_t *);

	// �����
	String& operator+= (const String &);
	String& operator+= (const char *);
	String& operator+= (const wchar_t *);
	String operator+ (const String &);
	String operator+ (const char *);
	String operator+ (const wchar_t *);

	// ��Ԫ�����
	friend String operator+ (const char *, const String &);
	friend String operator+ (const wchar_t*, const String &);

	// ����ת��������
	E2D_OP_EXPLICIT operator const wchar_t* () const;
	E2D_OP_EXPLICIT operator wchar_t* () const;
	E2D_OP_EXPLICIT operator const char* () const;
	E2D_OP_EXPLICIT operator char* () const;

	// �Ƚ������
	bool operator== (const String &) const;
	bool operator== (const char *) const;
	bool operator== (const wchar_t *) const;
	bool operator!= (const String &) const;
	bool operator!= (const char *) const;
	bool operator!= (const wchar_t *) const;
	bool operator> (const String &) const;
	bool operator>= (const String &) const;
	bool operator< (const String &) const;
	bool operator<= (const String &) const;

	// << �����������ַ�����
	String& operator<< (const String &);
	String& operator<< (const char *);
	String& operator<< (char *);
	String& operator<< (const wchar_t *);
	String& operator<< (wchar_t *);
	String& operator<< (int value);
	String& operator<< (unsigned int value);
	String& operator<< (float value);
	String& operator<< (double value);

	// ���������
	wchar_t& operator[] (int);

	friend std::ostream& operator<< (std::ostream &, const String &);
	friend std::wostream& operator<< (std::wostream &, const String &);

	friend std::istream& operator>> (std::istream &, String &);
	friend std::wistream& operator>> (std::wistream &, String &);

private:
	std::wstring _str;
};


// ��ɫ
class Color
{
public:
	Color();

	Color(
		float r,
		float g,
		float b
	);

	Color(
		float r,
		float g,
		float b,
		float alpha
	);

	Color(
		UINT rgb
	);

	Color(
		UINT rgb,
		float alpha
	);

	D2D1_COLOR_F toD2DColorF() const;

public:
	enum Value : UINT
	{
		Black = 0x000000,
		Blue = 0x0000FF,
		BlueViolet = 0x8A2BE2,
		Brown = 0xA52A2A,
		Chocolate = 0xD2691E,
		DarkBlue = 0x00008B,
		DarkGray = 0xA9A9A9,
		DarkGreen = 0x006400,
		DarkOrange = 0xFF8C00,
		DarkRed = 0x8B0000,
		DarkViolet = 0x9400D3,
		ForestGreen = 0x228B22,
		Gold = 0xFFD700,
		Gray = 0x808080,
		Green = 0x008000,
		GreenYellow = 0xADFF2F,
		LightBlue = 0xADD8E6,
		LightCyan = 0xE0FFFF,
		LightGreen = 0x90EE90,
		LightGray = 0xD3D3D3,
		LightPink = 0xFFB6C1,
		LightSeaGreen = 0x20B2AA,
		LightSkyBlue = 0x87CEFA,
		LightYellow = 0xFFFFE0,
		Orange = 0xFFA500,
		OrangeRed = 0xFF4500,
		Pink = 0xFFC0CB,
		Purple = 0x800080,
		Red = 0xFF0000,
		Silver = 0xC0C0C0,
		SkyBlue = 0x87CEEB,
		Snow = 0xFFFAFA,
		Violet = 0xEE82EE,
		Wheat = 0xF5DEB3,
		White = 0xFFFFFF,
		WhiteSmoke = 0xF5F5F5,
		Wood = 0xDEB887,
		Yellow = 0xFFFF00,
		Yellow_Green = 0x9ACD32
	};

private:
	void _init(
		UINT rgb,
		float alpha
	);

private:
	float r;
	float g;
	float b;
	float a;
};


// ��������
class Function
{
public:
	Function();

	Function(
		std::nullptr_t
	);

	Function(
		std::function<void()> func
	);

	template<typename Func>
	Function(Func func) : _func(func) {}

	template<typename Func, typename Object>
	Function(
		Func&& func,	/* ����ĳ�Ա���� */
		Object&& obj	/* ����ָ�� */
	)
	{
		_func = std::bind(func, obj);
	}

	void operator() (void) const;

	E2D_OP_EXPLICIT operator bool() const;

protected:
	std::function<void()> _func;
};


// ʱ���
class Duration
{
public:
	Duration();

	explicit Duration(
		int ms
	);

	explicit Duration(
		const std::chrono::milliseconds& ms
	);

	// ��ȡ������
	int milliseconds() const;

	// ��ȡ����
	float seconds() const;

	bool operator== (const Duration &) const;
	bool operator!= (const Duration &) const;
	bool operator> (const Duration &) const;
	bool operator>= (const Duration &) const;
	bool operator< (const Duration &) const;
	bool operator<= (const Duration &) const;

	Duration operator + (Duration const & other) const;
	Duration operator - (Duration const & other) const;

protected:
	std::chrono::milliseconds _ms;
};


// ʱ���
class Time
{
public:
	Time();

	explicit Time(
		const std::chrono::steady_clock::time_point& time
	);

	// ��ȡʱ���
	time_t getTimeStamp() const;

	Time operator + (Duration const & other) const;
	Time& operator += (Duration const &);
	
	Duration operator - (Time const & other) const;

	// ��ȡ��ǰʱ��
	static Time now();

protected:
	std::chrono::steady_clock::time_point _timePoint;
};


// ����
class Font
{
public:
	String	family;			// ������
	float	size;			// �ֺ�
	UINT	weight;			// ��ϸֵ
	bool	italic;			// б��

public:
	// �����ϸֵ
	enum Weight : UINT
	{
		Thin = 100,
		ExtraLight = 200,
		Light = 300,
		Normal = 400,
		Medium = 500,
		Bold = 700,
		ExtraBold = 800,
		Black = 900,
		ExtraBlack = 950
	};

public:
	Font();

	explicit Font(
		const String& family,
		float size = 22,
		UINT weight = Font::Weight::Normal,
		bool italic = false
	);
};


// ����ֵ
enum class MouseCode : int
{
	Left,		/* ������ */
	Right,		/* ����Ҽ� */
	Middle		/* ����м� */
};


// ���̼�ֵ
enum class KeyCode : int
{
	Unknown = 0,
	Up = 0xC8,
	Left = 0xCB,
	Right = 0xCD,
	Down = 0xD0,
	Enter = 0x1C,
	Space = 0x39,
	Esc = 0x01,
	Q = 0x10,
	W = 0x11,
	E = 0x12,
	R = 0x13,
	T = 0x14,
	Y = 0x15,
	U = 0x16,
	I = 0x17,
	O = 0x18,
	P = 0x19,
	A = 0x1E,
	S = 0x1F,
	D = 0x20,
	F = 0x21,
	G = 0x22,
	H = 0x23,
	J = 0x24,
	K = 0x25,
	L = 0x26,
	Z = 0x2C,
	X = 0x2D,
	C = 0x2E,
	V = 0x2F,
	B = 0x30,
	N = 0x31,
	M = 0x32,
	Num1 = 0x02,
	Num2 = 0x03,
	Num3 = 0x04,
	Num4 = 0x05,
	Num5 = 0x06,
	Num6 = 0x07,
	Num7 = 0x08,
	Num8 = 0x09,
	Num9 = 0x0A,
	Num0 = 0x0B,
	Numpad7 = 0x47,
	Numpad8 = 0x48,
	Numpad9 = 0x49,
	Numpad4 = 0x4B,
	Numpad5 = 0x4C,
	Numpad6 = 0x4D,
	Numpad1 = 0x4F,
	Numpad2 = 0x50,
	Numpad3 = 0x51,
	Numpad0 = 0x52,
};


// ������Ϣ
class KeyEvent
{
public:
	// ������Ϣ����
	enum class Type : int
	{
		Down = 0x0100,	// ����
		Up				// ̧��
	};

public:
	explicit KeyEvent(
		UINT message,
		WPARAM wParam,
		LPARAM lParam
	);

	// ��ȡ������ֵ
	KeyCode getCode() const;

	// ��ȡ��������
	int getCount() const;

	// ��ȡ�¼�����
	KeyEvent::Type getType() const;

	// VK ��ֵת��
	static KeyCode convertKeyCode(
		WPARAM wParam
	);

protected:
	int _count;
	KeyCode _code;
	KeyEvent::Type _type;
};


// �����Ϣ
class MouseEvent
{
public:
	// �����Ϣ����
	enum class Type : int
	{
		Move = 0x0200,		// ����ƶ�
		LeftDown,			// ����������
		LeftUp,				// ������̧��
		LeftDoubleClick,	// ������˫��
		RightDown,			// ����Ҽ�����
		RightUp,			// ����Ҽ�̧��
		RightDoubleClick,	// ����Ҽ�˫��
		MiddleDown,			// ����м�����
		MiddleUp,			// ����м�̧��
		MiddleDoubleClick,	// ����м�˫��
		Wheel				// ��������
	};

public:
	explicit MouseEvent(
		UINT message,
		WPARAM wParam,
		LPARAM lParam
	);

	float getX() const;

	float getY() const;

	Point getPos() const;

	// ��ȡ�¼�����
	MouseEvent::Type getType() const;

	float getWheelDelta() const;

	// Shift ���Ƿ���
	bool isShiftDown() const;

	// Ctrl ���Ƿ���
	bool isCtrlDown() const;

protected:
	bool _shiftDown;
	bool _ctrlDown;
	float _wheelDelta;
	Point _pos;
	MouseEvent::Type _type;
};


class Node;

// ��ײ��
class Collider
{
public:
	// ��ײ����״
	enum class Shape
	{
		None,		/* �� */
		Rect,		/* ���� */
		Circle,		/* Բ�� */
		Ellipse		/* ��Բ�� */
	};

	// ��ײ�彻����ϵ
	enum class Relation : int
	{
		Unknown = 0,		/* ��ϵ��ȷ�� */
		Disjoin = 1,		/* û�н��� */
		IsContained = 2,	/* ��ȫ������ */
		Contains = 3,		/* ��ȫ���� */
		Overlap = 4			/* �����ص� */
	};

public:
	explicit Collider(
		Node * parent
	);

	virtual ~Collider();

	// ������ײ����״
	void setShape(
		Shape shape
	);

	// �Ƿ񴥷���ײ�¼�
	void setCollisionNotify(
		bool notify
	);

	// ���û�رո���ײ��
	void setEnabled(
		bool enabled
	);

	// ������ײ��Ŀɼ���
	void setVisible(
		bool visible
	);

	// ���û�����ɫ
	void setColor(
		Color color
	);

	// �ж�����ײ��Ľ�����ϵ
	Relation getRelationWith(
		Collider * pCollider
	) const;

	// �Ƿ�������ײ��
	bool isEnabled() const;

	// �Ƿ�ɼ�
	bool isVisible() const;

	// �Ƿ񴥷���ײ�¼�
	bool isCollisionNotify() const;

	// ��ȡ������ɫ
	Color getColor() const;

	// ��ȡ��״
	Shape getShape() const;

	// ��ȡ�󶨽ڵ�
	Node* getNode() const;

	// ��ȡ ID2D1Geometry* ����
	ID2D1Geometry* getGeometry() const;

	// ��������
	void recreate();

	// ��Ⱦ��ײ��
	void render();

protected:
	E2D_DISABLE_COPY(Collider);

protected:
	bool	_enabled;
	bool	_visible;
	bool	_notify;
	Color	_color;
	Node *	_parentNode;
	Shape	_shape;
	ID2D1Geometry* _geometry;
};


// ��ײ�¼�
class Collision
{
public:
	Collision();

	explicit Collision(
		Node* node,
		Collider::Relation relation
	);

	~Collision();

	// ��ȡ������ײ�ڵ�
	Node* getNode() const;

	// ��ȡ������ϵ
	Collider::Relation getRelation() const;

protected:
	Node* _node;
	Collider::Relation _relation;
};


// ��Դ
class Resource
{
public:
	Resource(
		const String& fileName		/* �ļ�·�� */
	);

	Resource(
		size_t resNameId,			/* ��Դ���� */
		const String& resType		/* ��Դ���� */
	);

	// �Ƿ��Ǳ����ļ�
	bool isFile() const;

	const String& getFileName() const;

	size_t getResNameId() const;

	const String& getResType() const;

	size_t getKey() const;

	// �Ƚ������
	bool operator> (const Resource &) const;
	bool operator>= (const Resource &) const;
	bool operator< (const Resource &) const;
	bool operator<= (const Resource &) const;

protected:
	bool	_isFile;
	size_t	_resNameId;
	String	_resType;
	String	_fileName;
};


// ���ü�������
class Ref
{
public:
	Ref();

	virtual ~Ref();

	// �������ü���
	void retain();

	// �������ü���
	void release();

	// ��ȡ���ü���
	int getRefCount() const;

protected:
	E2D_DISABLE_COPY(Ref);

private:
	int _refCount;
};


// ͼƬ
class Image :
	public Ref
{
public:
	Image();

	explicit Image(
		const Resource& res
	);

	explicit Image(
		const Resource& res,
		const Rect& cropRect	/* �ü����� */
	);

	explicit Image(
		const String& fileName
	);

	explicit Image(
		const String& fileName,
		const Rect& cropRect	/* �ü����� */
	);

	virtual ~Image();

	// ����ͼƬ��Դ
	bool open(
		const Resource& res
	);

	// ����ͼƬ��Դ
	bool open(
		const String& fileName
	);

	// ��ͼƬ�ü�Ϊ����
	void crop(
		const Rect& cropRect	/* �ü����� */
	);

	// ��ȡ���
	virtual float getWidth() const;

	// ��ȡ�߶�
	virtual float getHeight() const;

	// ��ȡ��С
	virtual Size getSize() const;

	// ��ȡԴͼƬ���
	virtual float getSourceWidth() const;

	// ��ȡԴͼƬ�߶�
	virtual float getSourceHeight() const;

	// ��ȡԴͼƬ��С
	virtual Size getSourceSize() const;
	
	// ��ȡ�ü�λ�� X ����
	virtual float getCropX() const;

	// ��ȡ�ü�λ�� Y ����
	virtual float getCropY() const;

	// ��ȡ�ü�λ��
	virtual Point getCropPos() const;

	// ��ȡ ID2D1Bitmap ����
	ID2D1Bitmap * getBitmap();

	// Ԥ����ͼƬ��Դ
	static bool preload(
		const Resource& res
	);

	// ��ջ���
	static void clearCache();

protected:
	E2D_DISABLE_COPY(Image);

	// ���� Bitmap
	void _setBitmap(
		ID2D1Bitmap * bitmap
	);

protected:
	Rect _cropRect;
	ID2D1Bitmap * _bitmap;

	static std::map<Resource, ID2D1Bitmap*> _bitmapCache;
};


// ����
class Scene :
	public Ref
{
public:
	Scene();

	virtual ~Scene();

	// ���볡��
	virtual void onEnter() {}

	// �˳�����
	virtual void onExit() {}

	// ������Ϣ
	// ˵�������� false ����ֹ��Ϣ��������
	virtual bool onKeyEvent(KeyEvent e) { return true; }

	// �����Ϣ
	// ˵�������� false ����ֹ��Ϣ��������
	virtual bool onMouseEvent(MouseEvent e) { return true; }

	// ��ײ��Ϣ
	virtual void onCollision(Collision collision) { }

	// �رմ���
	// ˵�������� false ����ֹ���ڹر�
	virtual bool onCloseWindow() { return true; }

	// ��д���������������ÿһ֡����ˢ��ʱִ��
	virtual void onUpdate() {}

	// ��������� onUpdate ����
	void setAutoUpdate(
		bool bAutoUpdate
	);

	// ��ӽڵ㵽����
	void add(
		Node * child,	/* Ҫ��ӵĽڵ� */
		int zOrder = 0	/* ��Ⱦ˳�� */
	);

	// ��Ӷ���ڵ㵽����
	virtual void add(
		const std::vector<Node*>& nodes,	/* �ڵ����� */
		int order = 0						/* ��Ⱦ˳�� */
	);

	// ɾ���ӽڵ�
	bool remove(
		Node * child
	);

	// ��ȡ������ͬ���ӽڵ�
	Node* getChild(
		const String& name
	) const;

	// ��ȡ����������ͬ���ӽڵ�
	std::vector<Node*> getChildren(
		const String& name
	) const;

	// ��ȡ�����ӽڵ�
	const std::vector<Node*>& getAllChildren() const;

	// ��ȡ���ڵ�
	Node * getRoot() const;

	// ��Ⱦ��������
	void render();

	// ���³�������
	void update();

	// �ַ������Ϣ
	void dispatch(
		const MouseEvent& e
	);

	// �ַ�������Ϣ
	void dispatch(
		const KeyEvent& e
	);

protected:
	E2D_DISABLE_COPY(Scene);

protected:
	bool _autoUpdate;
	Node * _root;
};


}


namespace e2d
{
	struct autorelease_t { };

	extern autorelease_t const autorelease;
}

void* operator new(
	size_t size,
	e2d::autorelease_t const&
	) E2D_NOEXCEPT;

void operator delete(
	void* block,
	e2d::autorelease_t const&
	) E2D_NOEXCEPT;
