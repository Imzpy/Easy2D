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
	virtual void handle(KeyEvent e) = 0;
};


// �����Ϣ����ӿ�
class MouseEventHandler
{
public:
	// ���������Ϣ
	virtual void handle(MouseEvent e) = 0;
};


// ��ײ��Ϣ����ӿ�
class CollisionHandler
{
public:
	// ������ײ��Ϣ
	virtual void handle(Collision collision) = 0;
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
		float posX;			// X ����
		float posY;			// Y ����
		float width;		// ���
		float height;		// �߶�
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
	bool isVisible() const;

	// ��ȡ�ڵ�����
	const String& getName() const;

	// ��ȡ�ڵ����Ƶ� Hash ֵ
	size_t getHashName() const;

	// ��ȡ�ڵ��ͼ˳��
	int getOrder() const;

	// ��ȡ�ڵ������
	float getPosX() const;

	// ��ȡ�ڵ�������
	float getPosY() const;

	// ��ȡ�ڵ�����
	Point getPos() const;

	// ��ȡ�ڵ���
	float getWidth() const;

	// ��ȡ�ڵ�߶�
	float getHeight() const;

	// ��ȡ�ڵ��ȣ����������ţ�
	float getRealWidth() const;

	// ��ȡ�ڵ�߶ȣ����������ţ�
	float getRealHeight() const;

	// ��ȡ�ڵ��С�����������ţ�
	Size getRealSize() const;

	// ��ȡ�ڵ��ê��
	float getAnchorX() const;

	// ��ȡ�ڵ��ê��
	float getAnchorY() const;

	// ��ȡ�ڵ��С
	Size getSize() const;

	// ��ȡ�ڵ�������ű���
	float getScaleX() const;

	// ��ȡ�ڵ��������ű���
	float getScaleY() const;

	// ��ȡ�ڵ������б�Ƕ�
	float getSkewX() const;

	// ��ȡ�ڵ�������б�Ƕ�
	float getSkewY() const;

	// ��ȡ�ڵ���ת�Ƕ�
	float getRotation() const;

	// ��ȡ�ڵ�͸����
	float getOpacity() const;

	// ��ȡ�ڵ�����
	Property getProperty() const;

	// ��ȡ�������
	Property getExtrapolate() const;

	// ��ȡ�ڵ���ײ��
	Collider * getCollider();

	// ��ȡ���ڵ�
	Node * getParent() const;

	// ��ȡ�ڵ����ڳ���
	Scene * getParentScene() const;

	// ���ýڵ��Ƿ���ʾ
	void setVisible(
		bool value
	);

	// ���ýڵ�����
	void setName(
		const String& name
	);

	// ���ýڵ������
	virtual void setPosX(
		float x
	);

	// ���ýڵ�������
	virtual void setPosY(
		float y
	);

	// ���ýڵ�����
	virtual void setPos(
		const Point & point
	);

	// ���ýڵ�����
	virtual void setPos(
		float x,
		float y
	);

	// �ڵ�����̶�
	virtual void setPosFixed(
		bool fixed
	);

	// �ƶ��ڵ�
	virtual void movePosX(
		float x
	);

	// �ƶ��ڵ�
	virtual void movePosY(
		float y
	);

	// �ƶ��ڵ�
	virtual void movePos(
		float x,
		float y
	);

	// �ƶ��ڵ�
	virtual void movePos(
		const Vector2 & v
	);

	// ���ýڵ��ͼ˳��
	// Ĭ��Ϊ 0
	virtual void setOrder(
		int order
	);

	// ���ú������ű���
	// Ĭ��Ϊ 1.0
	virtual void setScaleX(
		float scaleX
	);

	// �����������ű���
	// Ĭ��Ϊ 1.0
	virtual void setScaleY(
		float scaleY
	);

	// �������ű���
	// Ĭ��Ϊ (1.0, 1.0)
	virtual void setScale(
		float scaleX,
		float scaleY
	);

	// �������ű���
	// Ĭ��Ϊ 1.0
	virtual void setScale(
		float scale
	);

	// ���ú�����б�Ƕ�
	// Ĭ��Ϊ 0
	virtual void setSkewX(
		float angleX
	);

	// ����������б�Ƕ�
	// Ĭ��Ϊ 0
	virtual void setSkewY(
		float angleY
	);

	// ������б�Ƕ�
	// Ĭ��Ϊ (0, 0)
	virtual void setSkew(
		float angleX,
		float angleY
	);

	// ������ת�Ƕ�
	// Ĭ��Ϊ 0
	virtual void setRotation(
		float rotation
	);

	// ����͸����
	// Ĭ��Ϊ 1.0, ��Χ [0, 1]
	virtual void setOpacity(
		float opacity
	);

	// ����ê��ĺ���λ��
	// Ĭ��Ϊ 0, ��Χ [0, 1]
	virtual void setAnchorX(
		float anchorX
	);

	// ����ê�������λ��
	// Ĭ��Ϊ 0, ��Χ [0, 1]
	virtual void setAnchorY(
		float anchorY
	);

	// ����ê��λ��
	// Ĭ��Ϊ (0, 0), ��Χ [0, 1]
	virtual void setAnchor(
		float anchorX,
		float anchorY
	);

	// �޸Ľڵ���
	virtual void setWidth(
		float width
	);

	// �޸Ľڵ�߶�
	virtual void setHeight(
		float height
	);

	// �޸Ľڵ��С
	virtual void setSize(
		float width,
		float height
	);

	// �޸Ľڵ��С
	virtual void setSize(
		Size size
	);

	// ���ýڵ�����
	virtual void setProperty(
		Property prop
	);

	// ���û�ر���Ⱦ����ü�
	virtual void setClipEnabled(
		bool enabled
	);

	// �жϵ��Ƿ��ڽڵ���
	bool containsPoint(
		const Point& point
	);

	// �ж��������Ƿ��ཻ
	bool intersects(
		Node * node
	);

	// ����ӽڵ�
	void addChild(
		Node * child,
		int order = 0	/* ��Ⱦ˳�� */
	);

	// ��Ӷ���ӽڵ�
	void addChild(
		const std::vector<Node*>& nodes,	/* �ڵ����� */
		int order = 0						/* ��Ⱦ˳�� */
	);

	// ��ȡ����������ͬ���ӽڵ�
	std::vector<Node*> getChildren(
		const String& name
	) const;

	// ��ȡ������ͬ���ӽڵ�
	Node* getChild(
		const String& name
	) const;

	// ��ȡ�����ӽڵ�
	const std::vector<Node*>& getAllChildren() const;

	// ��ȡ�ӽڵ�����
	int getChildrenCount() const;

	// �Ƴ��ӽڵ�
	bool removeChild(
		Node * child
	);

	// �Ƴ�����������ͬ���ӽڵ�
	void removeChildren(
		const String& childName
	);

	// �Ƴ����нڵ�
	void removeAllChildren();

	// �Ӹ��ڵ��Ƴ�
	void removeFromParent();

	// ִ�ж���
	void runAction(
		Action * action
	);

	// ��������
	void resumeAction(
		const String& name
	);

	// ��ͣ����
	void pauseAction(
		const String& name
	);

	// ֹͣ����
	void stopAction(
		const String& name
	);

	// ����������ͣ����
	void resumeAllActions();

	// ��ͣ���ж���
	void pauseAllActions();

	// ֹͣ���ж���
	void stopAllActions();

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
	float		_posX;
	float		_posY;
	float		_width;
	float		_height;
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
	void setOutlineVisible(
		bool visible
	);

	// �򿪻�ر���ײ����ӻ�
	// Ĭ�ϣ��ر�
	void setColliderVisible(
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
	void crop(
		const Rect& cropRect	/* �ü����� */
	);

	// ��ȡ Image ����
	Image * getImage() const;

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
	const String& getText() const;

	// ��ȡ����
	const Font& getFont() const;

	// ��ȡ�ı���ʽ
	const Style& getStyle() const;

	// ��ȡ������
	const String& getFontFamily() const;

	// ��ȡ��ǰ�ֺ�
	float getFontSize() const;

	// ��ȡ��ǰ�����ϸֵ
	UINT getFontWeight() const;

	// ��ȡ������ɫ
	const Color& getColor() const;

	// ��ȡ�����ɫ
	const Color& getOutlineColor() const;

	// ��ȡ����߿�
	float getOutlineWidth() const;

	// ��ȡ������ཻ��ʽ
	Stroke getOutlineStroke() const;

	// ��ȡ�ı���ʾ����
	int getLineCount() const;

	// �Ƿ���б��
	bool isItalic() const;

	// �Ƿ���ʾɾ����
	bool hasStrikethrough() const;

	// �Ƿ���ʾ�»���
	bool hasUnderline() const;

	// �Ƿ���ʾ���
	bool hasOutline() const;

	// �����ı�
	void setText(
		const String& text
	);

	// �����ı���ʽ
	void setStyle(
		const Style& style
	);

	// ��������
	void setFont(
		const Font& font
	);

	// ����������
	void setFontFamily(
		const String& family
	);

	// �����ֺţ�Ĭ��ֵΪ 22��
	void setFontSize(
		float size
	);

	// ���������ϸֵ��Ĭ��ֵΪ Text::Font::Weight::Normal��
	void setFontWeight(
		UINT weight
	);

	// ����������ɫ��Ĭ��ֵΪ Color::WHITE��
	void setColor(
		Color color
	);

	// ��������б�壨Ĭ��ֵΪ false��
	void setItalic(
		bool value
	);

	// �򿪻�ر��ı��Զ����У�Ĭ��Ϊ�رգ�
	void setWrapping(
		bool wrapping
	);

	// �����ı��Զ����еĿ�ȣ�Ĭ��Ϊ 0��
	void setWrappingWidth(
		float wrappingWidth
	);

	// �����м�ࣨĬ��Ϊ 0��
	void setLineSpacing(
		float lineSpacing
	);

	// ���ö��뷽ʽ��Ĭ��Ϊ Align::Left��
	void setAlignment(
		Align align
	);

	// �����»��ߣ�Ĭ��ֵΪ false��
	void setUnderline(
		bool hasUnderline
	);

	// ����ɾ���ߣ�Ĭ��ֵΪ false��
	void setStrikethrough(
		bool hasStrikethrough
	);

	// �����Ƿ���ʾ���
	void setOutline(
		bool hasOutline
	);

	// ���������ɫ
	void setOutlineColor(
		Color outlineColor
	);

	// ��������߿�
	void setOutlineWidth(
		float outlineWidth
	);

	// ����������ཻ��ʽ
	void setOutlineStroke(
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
	bool isEnable() const;

	// ���ð�ť���û����
	void setEnabled(
		bool enabled
	);

	// ����һ���������ʾ�İ�ť
	virtual void setNormal(
		Node * normal
	);

	// ����������밴ťʱ��ʾ�İ�ť
	virtual void setMouseOver(
		Node * mouseover
	);

	// ������갴�°�ťʱ��ʾ�İ�ť
	virtual void setSelected(
		Node * selected
	);

	// ���ð�ť������ʱ��ʾ�İ�ť
	virtual void setDisabled(
		Node * disabled
	);

	// ���ð�ť������ִ�к���
	void setClickFunc(
		const Function& func
	);

	// ����ê��λ��
	// Ĭ��Ϊ (0, 0), ��Χ [0, 1]
	virtual void setAnchor(
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
	bool isChecked() const;

	// ���ÿ��ذ�ť��״̬
	void setChecked(
		bool checked
	);

	// ���ð�ť��״̬����ʾ�İ�ť
	virtual void setNormal(
		Node * normal
	) override;

	// ���ð�ť��״̬�£�������밴ťʱ��ʾ�İ�ť
	virtual void setMouseOver(
		Node * mouseover
	) override;

	// ���ð�ť��״̬�£���갴�°�ťʱ��ʾ�İ�ť
	virtual void setSelected(
		Node * selected
	) override;

	// ���ð�ť��״̬�£�������ʱ��ʾ�İ�ť
	virtual void setDisabled(
		Node * disabled
	) override;

	// ���ð�ť�ر�״̬����ʾ�İ�ť
	void setNormalOff(
		Node * normal
	);

	// ���ð�ť�ر�״̬�£�������밴ťʱ��ʾ�İ�ť
	void setMouseOverOff(
		Node * mouseover
	);

	// ���ð�ť�ر�״̬�£���갴�°�ťʱ��ʾ�İ�ť
	void setSelectedOff(
		Node * selected
	);

	// ���ð�ť�ر�״̬�£���ť������ʱ��ʾ�İ�ť
	void setDisabledOff(
		Node * disabled
	);

	// ����ê��λ��
	// Ĭ��Ϊ (0, 0), ��Χ [0, 1]
	virtual void setAnchor(
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
	bool isEnable() const;

	// ��ȡ�˵��еİ�ť����
	size_t getButtonCount() const;

	// ���ò˵����û����
	void setEnabled(
		bool enabled
	);

	// ��Ӱ�ť
	void addButton(
		Button * button
	);

	// �Ƴ���ť
	bool removeButton(
		Button * button
	);

	// ��ȡ���а�ť
	const std::vector<Button*>& getAllButtons() const;

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
	void setLineColor(
		const Color& color
	);

	// ���������ɫ
	void setFillColor(
		const Color& color
	);

	// �����������
	void setStrokeWidth(
		float width
	);

	// ���������ཻ��ʽ
	void setStrokeStyle(
		Stroke strokeStyle
	);

	// ��ȡ������ɫ
	Color getLineColor() const;

	// ��ȡ�����ɫ
	Color getFillColor() const;

	// ��ȡ�������
	float getStrokeWidth() const;

	// ��ȡ�����ཻ��ʽ
	Stroke getStrokeStyle() const;

	// ��ֱ��
	void drawLine(
		const Point& begin,
		const Point& end
	);

	// ��Բ�α߿�
	void drawCircle(
		const Point& center,
		float radius
	);

	// ����Բ�α߿�
	void drawEllipse(
		const Point& center,
		float radiusX,
		float radiusY
	);

	// �����α߿�
	void drawRect(
		const Rect& rect
	);

	// ��Բ�Ǿ��α߿�
	void drawRoundedRect(
		const Rect& rect,
		float radiusX,
		float radiusY
	);

	// ���Բ��
	void fillCircle(
		const Point& center,
		float radius
	);

	// �����Բ��
	void fillEllipse(
		const Point& center,
		float radiusX,
		float radiusY
	);

	// ������
	void fillRect(
		const Rect& rect
	);

	// ���Բ�Ǿ���
	void fillRoundedRect(
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