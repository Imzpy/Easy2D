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
	double x;	// X ����
	double y;	// Y ����

public:
	Point();

	Point(double x, double y);

	Point(const Point& other);

	Point operator + (Point const & point) const;
	Point operator - (Point const & point) const;
	Point operator * (double const & point) const;
	Point operator / (double const & point) const;
	Point operator - () const;
	bool operator== (const Point& point) const;

	operator e2d::Size() const;

	// �ж���������
	static double distance(const Point&, const Point&);
};


// ��ά����
typedef Point Vector2;


// ��С
class Size
{
public:
	double width;	// ���
	double height;	// �߶�

public:
	Size();

	Size(double width, double height);

	Size(const Size& other);

	Size operator + (Size const & size) const;
	Size operator - (Size const & size) const;
	Size operator * (double const & size) const;
	Size operator / (double const & size) const;
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
	
	Rect(double x, double y, double width, double height);
	
	Rect(const Point& pos, const Size& size);
	
	Rect(const Rect& other);
	
	Rect& operator= (const Rect& other);

	bool operator== (const Rect& rect) const;
	
	// ���þ���
	void setRect(
		double x, 
		double y, 
		double width, 
		double height
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
	unsigned int getHashCode() const;

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
		double r,
		double g,
		double b
	);

	Color(
		double r,
		double g,
		double b,
		double alpha
	);

	Color(
		UINT rgb
	);

	Color(
		UINT rgb,
		double alpha
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
		double alpha
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


// ����
class Font
{
public:
	String	family;			// ������
	double	size;			// �ֺ�
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
		double size = 22,
		UINT weight = Font::Weight::Normal,
		bool italic = false
	);
};


class Node;
class ColliderManager;

// ��ײ��
class Collider
{
	friend class Node;
	friend class ColliderManager;

public:
	// ��ײ�����
	enum class Type
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
	// ���û�رո���ײ��
	virtual void setEnabled(
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
	virtual Relation getRelationWith(
		Collider * pCollider
	) const;

	// ��ȡ������ɫ
	Color getColor() const;

	// ��ȡ ID2D1Geometry* ����
	ID2D1Geometry* getGeometry() const;

protected:
	Collider(
		Node * parent
	);

	virtual ~Collider();

	E2D_DISABLE_COPY(Collider);

	// ��������
	void _recreate();

	// ��Ⱦ��ײ��
	void _render();

protected:
	bool	_enabled;
	bool	_visible;
	Color	_color;
	Node *	_parentNode;
	Type	_type;
	ID2D1Geometry* _geometry;
};


// ��Դ
class Resource
{
public:
	Resource(
		const String& fileName		/* �ļ�·�� */
	);

	Resource(
		int resNameId,				/* ��Դ���� */
		const String& resType		/* ��Դ���� */
	);

	// �Ƿ�����Դ����
	bool isResource() const;

	const String& getFileName() const;

	int getResNameId() const;

	const String& getResType() const;

	int getKey() const;

	// �Ƚ������
	bool operator> (const Resource &) const;
	bool operator>= (const Resource &) const;
	bool operator< (const Resource &) const;
	bool operator<= (const Resource &) const;

protected:
	bool _isResource;
	String _fileName;
	int _resNameId;
	String _resType;
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
	virtual double getWidth() const;

	// ��ȡ�߶�
	virtual double getHeight() const;

	// ��ȡ��С
	virtual Size getSize() const;

	// ��ȡԴͼƬ���
	virtual double getSourceWidth() const;

	// ��ȡԴͼƬ�߶�
	virtual double getSourceHeight() const;

	// ��ȡԴͼƬ��С
	virtual Size getSourceSize() const;
	
	// ��ȡ�ü�λ�� X ����
	virtual double getCropX() const;

	// ��ȡ�ü�λ�� Y ����
	virtual double getCropY() const;

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
};


// ����
class Scene :
	public Ref
{
public:
	Scene();

	virtual ~Scene();

	// ��д��������������ڽ����������ʱ�Զ�ִ��
	virtual void onEnter() {}

	// ��д����������������뿪�������ʱ�Զ�ִ��
	virtual void onExit() {}

	// ��д��������������ڹرմ���ʱִ�У����� false ����ֹ���ڹرգ�
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

protected:
	E2D_DISABLE_COPY(Scene);

protected:
	bool _autoUpdate;
	Node * _root;
};


class Game;

// ��Ϸ����
class Config :
	public Ref
{
	friend class Game;

public:
	Config();

	virtual ~Config();

	// �޸���Ϸ����
	// Ĭ�ϣ���
	void setGameName(
		const String& name
	);

	// ��ʾ�����ؽڵ�����
	// Ĭ�ϣ�����
	void setOutlineVisible(
		bool visible
	);

	// �򿪻�ر�����
	// Ĭ�ϣ���
	void setSoundEnabled(
		bool enabled
	);

	// �򿪻�ر���ײ����
	// Ĭ�ϣ��ر�
	void setCollisionEnabled(
		bool enabled
	);

	// ���ýڵ��Ĭ�����ĵ�λ��
	// Ĭ�ϣ�(0,0)
	void setNodeDefaultPivot(
		Point pivot
	);

	// ���ýڵ��Ĭ����ײ������
	// Ĭ�ϣ�Collider::Type::None
	void setDefaultColliderType(
		Collider::Type type
	);

	// �򿪻�ر���ײ����ӻ�
	// Ĭ�ϣ��ر�
	void setColliderVisible(
		bool visible
	);

	// ��ȡ��Ϸ����
	String getGameName() const;

	// ��ȡ������״̬
	bool isSoundEnabled() const;

	// ��ȡ�ڵ�������ʾ״̬
	bool isOutlineVisible() const;

	// ��ȡ��ײ����״̬
	bool isCollisionEnabled() const;

	// ��ȡ�ڵ��Ĭ�����ĵ�λ��
	Point getNodeDefaultPivot() const;

	// ��ȡ�ڵ��Ĭ����ײ������
	Collider::Type getDefaultColliderType() const;

	// ��ȡ��ײ����ӻ�״̬
	bool isColliderVisible() const;

protected:
	virtual void _update();

protected:
	bool			_unconfigured;
	bool			_soundEnabled;
	bool			_outlineVisible;
	bool			_collisionEnabled;
	bool			_colliderVisible;
	String			_gameName;
	Point			_nodeDefPivot;
	Collider::Type	_nodeDefColliderType;
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

void* operator new[](
	size_t size,
	e2d::autorelease_t const&
	) E2D_NOEXCEPT;

void operator delete(
	void* block,
	e2d::autorelease_t const&
	) E2D_NOEXCEPT;

void operator delete[](
	void* block,
	e2d::autorelease_t const&
	) E2D_NOEXCEPT;
