#pragma once
#include "e2dbase.h"
#include "e2devent.h"

namespace e2d 
{


class Action;


// ��ͼ�ӿ�
class Drawable
{
public:
	// ��Ⱦͼ��
	virtual void draw(Renderer * renderer) const = 0;
};


// ���½ӿ�
class Updatable
{
public:
	// ��Ⱦͼ��
	virtual void update() = 0;
};


// ������Ϣ����ӿ�
class KeyEventHandler
{
public:
	// ��������Ϣ
	virtual void handle(const KeyEvent& e) = 0;
};


// �����Ϣ����ӿ�
class MouseEventHandler
{
public:
	// ���������Ϣ
	virtual void handle(const MouseEvent& e) = 0;
};


// ��ײ��Ϣ����ӿ�
class CollisionHandler
{
public:
	// ������ײ��Ϣ
	virtual void handle(const Collision& collision) = 0;
};


// �ڵ�
class Node :
	public Ref
{
	friend class Collider;

public:
	// �ڵ�����
	struct Property
	{
		Point position;		// ����
		Size size;			// ��С
		float anchorX;		// ê�� X ����
		float anchorY;		// ê�� Y ����
		float scaleX;		// ��������
		float scaleY;		// ��������
		float rotation;		// ��ת�Ƕ�
		float skewAngleX;	// ������б�Ƕ�
		float skewAngleY;	// ������б�Ƕ�

		Property operator+ (Property const & prop) const;
		Property operator- (Property const & prop) const;

		static const Property Origin;
	};

public:
	Node();

	virtual ~Node();

	// ��ȡ�ڵ���ʾ״̬
	virtual bool visible() const;

	// ��ȡ�ڵ�����
	const String& name() const;

	// ��ȡ�ڵ����Ƶ� Hash ֵ
	size_t hashName() const;

	// ��ȡ�ڵ��ͼ˳��
	int order() const;

	// ��ȡ�ڵ������
	float positionX() const;

	// ��ȡ�ڵ�������
	float positionY() const;

	// ��ȡ�ڵ�����
	const Point& position() const;

	// ��ȡ�ڵ���
	float width() const;

	// ��ȡ�ڵ�߶�
	float height() const;

	// ��ȡ�ڵ��С
	Size size() const;

	// ��ȡ�ڵ�ʵ�ʿ�ȣ����������ţ�
	float realWidth() const;

	// ��ȡ�ڵ�ʵ�ʸ߶ȣ����������ţ�
	float realHeight() const;

	// ��ȡ�ڵ�ʵ�ʴ�С�����������ţ�
	const Size& realSize() const;

	// ��ȡ�ڵ��ê��
	float anchorX() const;

	// ��ȡ�ڵ��ê��
	float anchorY() const;

	// ��ȡ�ڵ�������ű���
	float scaleX() const;

	// ��ȡ�ڵ��������ű���
	float scaleY() const;

	// ��ȡ�ڵ������б�Ƕ�
	float skewX() const;

	// ��ȡ�ڵ�������б�Ƕ�
	float skewY() const;

	// ��ȡ�ڵ���ת�Ƕ�
	float rotation() const;

	// ��ȡ�ڵ�͸����
	float opacity() const;

	// ��ȡ�ڵ�����
	Property properties() const;

	// ��ȡ�������
	Property extrapolate() const;

	// ���ýڵ��Ƿ���ʾ
	Node& visible(
		bool value
	);

	// ���ýڵ�����
	Node& name(
		const String& name
	);

	// ���ýڵ������
	virtual Node& positionX(
		float x
	);

	// ���ýڵ�������
	virtual Node& positionY(
		float y
	);

	// ���ýڵ�����
	virtual Node& position(
		const Point & point
	);

	// ���ýڵ�����
	virtual Node& position(
		float x,
		float y
	);

	// �ڵ�����̶�
	virtual Node& positionFixed(
		bool fixed
	);

	// �ƶ��ڵ�
	virtual Node& move(
		float x,
		float y
	);

	// �ƶ��ڵ�
	virtual Node& move(
		const Vector2 & v
	);

	// ���ýڵ��ͼ˳��
	// Ĭ��Ϊ 0
	virtual Node& order(
		int order
	);

	// ���ú������ű���
	// Ĭ��Ϊ 1.0
	virtual Node& scaleX(
		float scaleX
	);

	// �����������ű���
	// Ĭ��Ϊ 1.0
	virtual Node& scaleY(
		float scaleY
	);

	// �������ű���
	// Ĭ��Ϊ (1.0, 1.0)
	virtual Node& scale(
		float scaleX,
		float scaleY
	);

	// �������ű���
	// Ĭ��Ϊ 1.0
	virtual Node& scale(
		float scale
	);

	// ���ú�����б�Ƕ�
	// Ĭ��Ϊ 0
	virtual Node& skewX(
		float angleX
	);

	// ����������б�Ƕ�
	// Ĭ��Ϊ 0
	virtual Node& skewY(
		float angleY
	);

	// ������б�Ƕ�
	// Ĭ��Ϊ (0, 0)
	virtual Node& skew(
		float angleX,
		float angleY
	);

	// ������ת�Ƕ�
	// Ĭ��Ϊ 0
	virtual Node& rotation(
		float rotation
	);

	// ����͸����
	// Ĭ��Ϊ 1.0, ��Χ [0, 1]
	virtual Node& opacity(
		float opacity
	);

	// ����ê��ĺ���λ��
	// Ĭ��Ϊ 0, ��Χ [0, 1]
	virtual Node& anchorX(
		float anchorX
	);

	// ����ê�������λ��
	// Ĭ��Ϊ 0, ��Χ [0, 1]
	virtual Node& anchorY(
		float anchorY
	);

	// ����ê��λ��
	// Ĭ��Ϊ (0, 0), ��Χ [0, 1]
	virtual Node& anchor(
		float anchorX,
		float anchorY
	);

	// �޸Ľڵ���
	virtual Node& width(
		float width
	);

	// �޸Ľڵ�߶�
	virtual Node& height(
		float height
	);

	// �޸Ľڵ��С
	virtual Node& size(
		float width,
		float height
	);

	// �޸Ľڵ��С
	virtual Node& size(
		Size size
	);

	// ���ýڵ�����
	virtual Node& properties(
		Property prop
	);

	// ���û�ر���Ⱦ����ü�
	virtual Node& clipEnabled(
		bool enabled
	);

	// ����ӽڵ�
	Node& addChild(
		Node * child,
		int order = 0	/* ��Ⱦ˳�� */
	);

	// ��Ӷ���ӽڵ�
	Node& addChild(
		const std::vector<Node*>& nodes,	/* �ڵ����� */
		int order = 0						/* ��Ⱦ˳�� */
	);

	// ��ȡ�ڵ���ײ��
	Collider * collider();

	// ��ȡ���ڵ�
	Node * parent() const;

	// ��ȡ�ڵ����ڳ���
	Scene * parentScene() const;

	// ��ȡ������ͬ���ӽڵ�
	Node* child(
		const String& name
	) const;

	// ��ȡ�����ӽڵ�
	const std::vector<Node*>& children() const;

	// ��ȡ����������ͬ���ӽڵ�
	std::vector<Node*> children(
		const String& name
	) const;

	// ��ȡ�ӽڵ�����
	int childrenCount() const;

	// �Ƴ��ӽڵ�
	Node& removeChild(
		Node * child
	);

	// �Ƴ�����������ͬ���ӽڵ�
	Node& removeChildren(
		const String& childName
	);

	// �Ƴ����нڵ�
	Node& removeAllChildren();

	// �Ӹ��ڵ��Ƴ�
	Node& removeFromParent();

	// �жϵ��Ƿ��ڽڵ���
	bool containsPoint(
		const Point& point
	);

	// �ж��������Ƿ��ཻ
	bool intersects(
		Node * node
	);

	// ִ�ж���
	Node& runAction(
		Action * action
	);

	// ��������
	Node& resumeAction(
		const String& name
	);

	// ��ͣ����
	Node& pauseAction(
		const String& name
	);

	// ֹͣ����
	Node& stopAction(
		const String& name
	);

	// ����������ͣ����
	Node& resumeAllActions();

	// ��ͣ���ж���
	Node& pauseAllActions();

	// ֹͣ���ж���
	Node& stopAllActions();

	// �ַ������Ϣ
	virtual bool dispatch(
		const MouseEvent& e,
		bool handled
	);

	// �ַ�������Ϣ
	virtual bool dispatch(
		const KeyEvent& e,
		bool handled
	);

	// �����ڵ�
	virtual void visit(
		Game * game
	);

	// ��Ⱦ�ڵ�����
	virtual void drawOutline(
		Renderer * renderer
	);

	// ��Ⱦ��ײ������
	virtual void drawCollider();

protected:
	E2D_DISABLE_COPY(Node);

	// ���ýڵ����ڳ���
	void _setParentScene(
		Scene * scene
	);

	// �ӽڵ�����
	void _sortChildren();

	// ����ת������
	void _updateTransform();

	// ���½ڵ�͸����
	void _updateOpacity();

protected:
	String		_name;
	size_t		_hashName;
	Point		_position;
	Size		_size;
	float		_scaleX;
	float		_scaleY;
	float		_rotation;
	float		_skewAngleX;
	float		_skewAngleY;
	float		_displayOpacity;
	float		_realOpacity;
	float		_anchorX;
	float		_anchorY;
	int			_order;
	bool		_visible;
	bool		_clipEnabled;
	bool		_needSort;
	bool		_needTransform;
	bool		_positionFixed;
	Collider	_collider;
	Scene *		_parentScene;
	Node *		_parent;
	Property	_extrapolate;
	std::vector<Node*>	_children;
	D2D1::Matrix3x2F	_initialMatri;
	D2D1::Matrix3x2F	_finalMatri;
};


// ����
class Scene :
	public Node
{
public:
	Scene();

	virtual ~Scene();

	// ���볡��
	virtual void onEnter() {}

	// �˳�����
	virtual void onExit() {}

	// �رմ���
	// ˵�������� false ����ֹ���ڹر�
	virtual bool onCloseWindow() { return true; }

	// ��ʾ�����ؽڵ�����
	// Ĭ�ϣ�����
	Scene& outlineVisible(
		bool visible
	);

	// �򿪻�ر���ײ����ӻ�
	// Ĭ�ϣ��ر�
	Scene& colliderVisible(
		bool visible
	);

	// �����ڵ�
	virtual void visit(
		Game * game
	) override;

protected:
	E2D_DISABLE_COPY(Scene);

protected:
	bool _outlineVisible;
	bool _colliderVisible;
};


// ����
class Sprite :
	public Node,
	public Drawable
{
public:
	Sprite();

	explicit Sprite(
		Image * image
	);

	explicit Sprite(
		const Resource& res
	);

	explicit Sprite(
		const Resource& res,
		const Rect& cropRect	/* �ü����� */
	);

	explicit Sprite(
		const String& fileName
	);

	explicit Sprite(
		const String& fileName,
		const Rect& cropRect	/* �ü����� */
	);

	virtual ~Sprite();

	// ����ͼƬ�ļ�
	bool open(
		const Resource& res
	);

	// ����ͼƬ�ļ�
	bool open(
		const String& fileName
	);
	
	// ����ͼƬ
	bool open(
		Image * image
	);

	// ��ͼƬ�ü�Ϊ����
	Sprite& crop(
		const Rect& cropRect	/* �ü����� */
	);

	// ��ȡ Image ����
	Image * image() const;

	// ��Ⱦ����
	virtual void draw(
		Renderer * renderer
	) const override;

protected:
	E2D_DISABLE_COPY(Sprite);

protected:
	Image * _image;
};


// �ı�
class Text :
	public Node,
	public Drawable
{
public:
	// �ı����뷽ʽ
	enum class Align
	{
		Left,		/* ����� */
		Right,		/* �Ҷ��� */
		Center		/* ���ж��� */
	};

	// �ı���ʽ
	class Style
	{
	public:
		Color		color;				// ��ɫ
		Align		alignment;			// ���뷽ʽ
		bool		wrapping;			// ���Զ�����
		float		wrappingWidth;		// �Զ����п��
		float		lineSpacing;		// �м��
		bool		hasUnderline;		// �»���
		bool		hasStrikethrough;	// ɾ����
		bool		hasOutline;			// ��ʾ���
		Color		outlineColor;		// �����ɫ
		float		outlineWidth;		// ����߿�
		Stroke	outlineStroke;		// ������ཻ��ʽ

	public:
		Style();

		Style(
			Color color,
			Align alignment = Align::Left,
			bool wrapping = false,
			float wrappingWidth = 0.f,
			float lineSpacing = 0.f,
			bool hasUnderline = false,
			bool hasStrikethrough = false,
			bool hasOutline = true,
			Color outlineColor = Color(Color::Black, 0.5),
			float outlineWidth = 1.f,
			Stroke outlineStroke = Stroke::Round
		);
	};

public:
	Text();

	explicit Text(
		const String& text,						/* �������� */
		const Font& font = Font(),				/* ���� */
		const Style& style = Style()			/* �ı���ʽ */
	);

	virtual ~Text();

	// ��ȡ�ı�
	const String& text() const;

	// ��ȡ����
	const Font& font() const;

	// ��ȡ�ı���ʽ
	const Style& style() const;

	// ��ȡ������
	const String& fontFamily() const;

	// ��ȡ��ǰ�ֺ�
	float fontSize() const;

	// ��ȡ��ǰ�����ϸֵ
	UINT fontWeight() const;

	// ��ȡ������ɫ
	const Color& color() const;

	// ��ȡ�����ɫ
	const Color& outlineColor() const;

	// ��ȡ����߿�
	float outlineWidth() const;

	// ��ȡ������ཻ��ʽ
	Stroke outlineStroke() const;

	// ��ȡ�ı���ʾ����
	int lineCount() const;

	// �Ƿ���б��
	bool italic() const;

	// �Ƿ���ʾɾ����
	bool hasStrikethrough() const;

	// �Ƿ���ʾ�»���
	bool hasUnderline() const;

	// �Ƿ���ʾ���
	bool hasOutline() const;

	// �����ı�
	Text& text(
		const String& text
	);

	// �����ı���ʽ
	Text& style(
		const Style& style
	);

	// ��������
	Text& font(
		const Font& font
	);

	// ����������
	Text& fontFamily(
		const String& family
	);

	// �����ֺţ�Ĭ��ֵΪ 22��
	Text& fontSize(
		float size
	);

	// ���������ϸֵ��Ĭ��ֵΪ Text::Font::Weight::Normal��
	Text& fontWeight(
		UINT weight
	);

	// ����������ɫ��Ĭ��ֵΪ Color::WHITE��
	Text& color(
		Color color
	);

	// ��������б�壨Ĭ��ֵΪ false��
	Text& italic(
		bool value
	);

	// �򿪻�ر��ı��Զ����У�Ĭ��Ϊ�رգ�
	Text& wrapping(
		bool wrapping
	);

	// �����ı��Զ����еĿ�ȣ�Ĭ��Ϊ 0��
	Text& wrappingWidth(
		float wrappingWidth
	);

	// �����м�ࣨĬ��Ϊ 0��
	Text& lineSpacing(
		float lineSpacing
	);

	// ���ö��뷽ʽ��Ĭ��Ϊ Align::Left��
	Text& alignment(
		Align align
	);

	// �����»��ߣ�Ĭ��ֵΪ false��
	Text& underline(
		bool hasUnderline
	);

	// ����ɾ���ߣ�Ĭ��ֵΪ false��
	Text& strikethrough(
		bool hasStrikethrough
	);

	// �����Ƿ���ʾ���
	Text& outline(
		bool hasOutline
	);

	// ���������ɫ
	Text& outlineColor(
		Color outlineColor
	);

	// ��������߿�
	Text& outlineWidth(
		float outlineWidth
	);

	// ����������ཻ��ʽ
	Text& outlineStroke(
		Stroke outlineStroke
	);

	// ��Ⱦ����
	virtual void draw(
		Renderer * renderer
	) const override;

protected:
	E2D_DISABLE_COPY(Text);

	// �����Ű�����
	void _reset();

	// �������ָ�ʽ��
	void _createFormat();

	// �������ֲ���
	void _createLayout();

protected:
	String	_text;
	Font	_font;
	Style	_style;
	IDWriteTextFormat * _textFormat;
	IDWriteTextLayout * _textLayout;
};


class Button :
	public Node
{
public:
	Button();

	explicit Button(
		Node * normal,					/* ��ͨ״̬ */
		const Function& func = nullptr	/* ��ť������ִ�к��� */
	);

	explicit Button(
		Node * normal,					/* ��ͨ״̬ */
		Node * selected,				/* ��갴��״̬ */
		const Function& func = nullptr	/* ��ť������ִ�к��� */
	);

	explicit Button(
		Node * normal,					/* ��ͨ״̬ */
		Node * mouseover,				/* �������״̬ */
		Node * selected,				/* ��갴��״̬ */
		const Function& func = nullptr	/* ��ť������ִ�к��� */
	);

	explicit Button(
		Node * normal,					/* ��ͨ״̬ */
		Node * mouseover,				/* �������״̬ */
		Node * selected,				/* �������״̬ */
		Node * disabled,				/* ��ť����״̬ */
		const Function& func = nullptr	/* ��ť������ִ�к��� */
	);

	// ��ȡ��ť״̬�����û��ǽ���
	bool enabled() const;

	// ���ð�ť���û����
	Button& enabled(
		bool enabled
	);

	// ����һ���������ʾ�İ�ť
	virtual Button& normal(
		Node * normal
	);

	// ����������밴ťʱ��ʾ�İ�ť
	virtual Button& mouseover(
		Node * mouseover
	);

	// ������갴�°�ťʱ��ʾ�İ�ť
	virtual Button& selected(
		Node * selected
	);

	// ���ð�ť������ʱ��ʾ�İ�ť
	virtual Button& disabled(
		Node * disabled
	);

	// ���õ���ص�����
	Button& clickCallback(
		const Function& func
	);

	// ����ê��λ��
	// Ĭ��Ϊ (0, 0), ��Χ [0, 1]
	virtual Button& anchor(
		float anchorX,
		float anchorY
	) override;

	// �ַ������Ϣ
	virtual bool dispatch(
		const MouseEvent& e,
		bool handled
	) override;

	// �����ڵ�
	virtual void visit(
		Game * game
	) override;

protected:
	E2D_DISABLE_COPY(Button);

	// ��ť״̬ö��
	enum class Status { Normal, Mouseover, Selected };

	// ���ð�ť״̬
	virtual void _setStatus(Status status);

	// ˢ�°�ť��ʾ
	virtual void _updateVisible();

	// ִ�а�ť��������
	virtual void _runCallback();

protected:
	Node *		_normal;
	Node *		_mouseover;
	Node *		_selected;
	Node *		_disabled;
	bool		_enabled;
	bool		_isSelected;
	Status		_status;
	Function	_func;
};


class ToggleButton :
	public Button
{
public:
	ToggleButton();

	explicit ToggleButton(
		Node * onNormal,				/* ��ť��ʱ����ͨ״̬ */
		Node * offNormal,				/* ��ť�ر�ʱ����ͨ״̬ */
		const Function& func = nullptr	/* ��ť������ִ�к��� */
	);

	explicit ToggleButton(
		Node * onNormal,				/* ��ť��ʱ����ͨ״̬ */
		Node * offNormal,				/* ��ť�ر�ʱ����ͨ״̬ */
		Node * onSelected,				/* ��ť��ʱ����갴��״̬ */
		Node * offSelected,				/* ��ť�ر�ʱ����갴��״̬ */
		const Function& func = nullptr	/* ��ť������ִ�к��� */
	);

	explicit ToggleButton(
		Node * onNormal,				/* ��ť��ʱ����ͨ״̬ */
		Node * offNormal,				/* ��ť�ر�ʱ����ͨ״̬ */
		Node * onMouseOver,				/* ��ť��ʱ���������״̬ */
		Node * offMouseOver,			/* ��ť�ر�ʱ���������״̬ */
		Node * onSelected,				/* ��ť��ʱ����갴��״̬ */
		Node * offSelected,				/* ��ť�ر�ʱ����갴��״̬ */
		const Function& func = nullptr	/* ��ť������ִ�к��� */
	);

	explicit ToggleButton(
		Node * onNormal,				/* ��ť��ʱ����ͨ״̬ */
		Node * offNormal,				/* ��ť�ر�ʱ����ͨ״̬ */
		Node * onMouseOver,				/* ��ť��ʱ���������״̬ */
		Node * offMouseOver,			/* ��ť�ر�ʱ���������״̬ */
		Node * onSelected,				/* ��ť��ʱ����갴��״̬ */
		Node * offSelected,				/* ��ť�ر�ʱ����갴��״̬ */
		Node * onDisabled,				/* ��ť��ʱ������״̬ */
		Node * offDisabled,				/* ��ť�ر�ʱ������״̬ */
		const Function& func = nullptr	/* ��ť������ִ�к��� */
	);

	// ��ȡ����״̬
	bool checked() const;

	// ���ÿ��ذ�ť��״̬
	ToggleButton& checked(
		bool checked
	);

	// ���ð�ť��״̬����ʾ�İ�ť
	virtual ToggleButton& normal(
		Node * normal
	) override;

	// ���ð�ť��״̬�£�������밴ťʱ��ʾ�İ�ť
	virtual ToggleButton& mouseover(
		Node * mouseover
	) override;

	// ���ð�ť��״̬�£���갴�°�ťʱ��ʾ�İ�ť
	virtual ToggleButton& selected(
		Node * selected
	) override;

	// ���ð�ť��״̬�£�������ʱ��ʾ�İ�ť
	virtual ToggleButton& disabled(
		Node * disabled
	) override;

	// ���ð�ť�ر�״̬����ʾ�İ�ť
	ToggleButton& normalOff(
		Node * normal
	);

	// ���ð�ť�ر�״̬�£�������밴ťʱ��ʾ�İ�ť
	ToggleButton& mouseOverOff(
		Node * mouseover
	);

	// ���ð�ť�ر�״̬�£���갴�°�ťʱ��ʾ�İ�ť
	ToggleButton& selectedOff(
		Node * selected
	);

	// ���ð�ť�ر�״̬�£���ť������ʱ��ʾ�İ�ť
	ToggleButton& disabledOff(
		Node * disabled
	);

	// ����ê��λ��
	// Ĭ��Ϊ (0, 0), ��Χ [0, 1]
	virtual ToggleButton& anchor(
		float anchorX,
		float anchorY
	) override;

protected:
	E2D_DISABLE_COPY(ToggleButton);

	// ˢ�°�ť����
	virtual void _updateStatus();

	// ִ�а�ť��������
	virtual void _runCallback() override;

protected:
	Node*	_normalOn;
	Node*	_mouseoverOn;
	Node*	_selectedOn;
	Node*	_disabledOn;
	Node*	_normalOff;
	Node*	_mouseoverOff;
	Node*	_selectedOff;
	Node*	_disabledOff;
	bool	_checked;
};


class Menu :
	public Node
{
public:
	Menu();

	explicit Menu(
		const std::vector<Button*>& buttons	/* ��ť���� */
	);

	// ��ȡ�˵��Ƿ����
	bool enabled() const;

	// ��ȡ�˵��еİ�ť����
	int buttonCount() const;

	// ���ò˵����û����
	Menu& enabled(
		bool enabled
	);

	// ��Ӱ�ť
	Menu& addButton(
		Button * button
	);

	// �Ƴ���ť
	bool removeButton(
		Button * button
	);

	// ��ȡ���а�ť
	const std::vector<Button*>& buttons() const;

protected:
	E2D_DISABLE_COPY(Menu);

protected:
	bool _enabled;
	std::vector<Button*> _buttons;
};


// ����
class Canvas :
	public Node,
	public Drawable
{
public:
	Canvas(
		float width,
		float height
	);

	virtual ~Canvas();

	// ����������ɫ
	Canvas& lineColor(
		const Color& color
	);

	// ���������ɫ
	Canvas& fillColor(
		const Color& color
	);

	// �����������
	Canvas& strokeWidth(
		float width
	);

	// ���������ཻ��ʽ
	Canvas& strokeStyle(
		Stroke strokeStyle
	);

	// ��ȡ������ɫ
	Color lineColor() const;

	// ��ȡ�����ɫ
	Color fillColor() const;

	// ��ȡ�������
	float strokeWidth() const;

	// ��ȡ�����ཻ��ʽ
	Stroke strokeStyle() const;

	// ��ֱ��
	Canvas& drawLine(
		const Point& begin,
		const Point& end
	);

	// ��Բ�α߿�
	Canvas& drawCircle(
		const Point& center,
		float radius
	);

	// ����Բ�α߿�
	Canvas& drawEllipse(
		const Point& center,
		float radiusX,
		float radiusY
	);

	// �����α߿�
	Canvas& drawRect(
		const Rect& rect
	);

	// ��Բ�Ǿ��α߿�
	Canvas& drawRoundedRect(
		const Rect& rect,
		float radiusX,
		float radiusY
	);

	// ���Բ��
	Canvas& fillCircle(
		const Point& center,
		float radius
	);

	// �����Բ��
	Canvas& fillEllipse(
		const Point& center,
		float radiusX,
		float radiusY
	);

	// ������
	Canvas& fillRect(
		const Rect& rect
	);

	// ���Բ�Ǿ���
	Canvas& fillRoundedRect(
		const Rect& rect,
		float radiusX,
		float radiusY
	);

protected:
	E2D_DISABLE_COPY(Canvas);

protected:
	float _strokeWidth;
	Stroke _stroke;
	Renderer * _renderer;
	ID2D1RenderTarget * _renderTarget;
	ID2D1SolidColorBrush * _fillBrush;
	ID2D1SolidColorBrush * _lineBrush;
	ID2D1StrokeStyle * _strokeStyle;
};

}