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
	virtual void Draw() const = 0;
};


// ���½ӿ�
class Updatable
{
public:
	// ��Ⱦͼ��
	virtual void Update() = 0;
};


// ������Ϣ����ӿ�
class KeyEventHandler
{
public:
	// ��������Ϣ
	virtual void Handle(KeyEvent e) = 0;
};


// �����Ϣ����ӿ�
class MouseEventHandler
{
public:
	// ���������Ϣ
	virtual void Handle(MouseEvent e) = 0;
};


// ��ײ��Ϣ����ӿ�
class CollisionHandler
{
public:
	// ������ײ��Ϣ
	virtual void Handle(Collision collision) = 0;
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
		Point pos;			// ����
		Size size;			// ��С
		Point anchor;		// ê������
		Point scale;		// ����
		Point skew;			// ��б�Ƕ�
		float rotation;		// ��ת�Ƕ�

		Property operator+ (Property const & prop) const;
		Property operator- (Property const & prop) const;

		static const Property Origin;
	};

public:
	typedef std::vector<Node*> Nodes;
	typedef std::vector<Action*> Actions;

	Node();

	virtual ~Node();

	// ��ȡ�ڵ���ʾ״̬
	bool IsVisible() const;

	// ��ȡ�ڵ�����
	const String& GetName() const;

	// ��ȡ�ڵ����Ƶ� Hash ֵ
	size_t GetHashName() const;

	// ��ȡ�ڵ��ͼ˳��
	int GetOrder() const;

	// ��ȡ�ڵ������
	float GetPosX() const;

	// ��ȡ�ڵ�������
	float GetPosY() const;

	// ��ȡ�ڵ�����
	Point GetPos() const;

	// ��ȡ�ڵ���
	float GetWidth() const;

	// ��ȡ�ڵ�߶�
	float GetHeight() const;

	// ��ȡ�ڵ��ȣ����������ţ�
	float GetRealWidth() const;

	// ��ȡ�ڵ�߶ȣ����������ţ�
	float GetRealHeight() const;

	// ��ȡ�ڵ��С�����������ţ�
	Size GetRealSize() const;

	// ��ȡ�ڵ��ê��
	float GetAnchorX() const;

	// ��ȡ�ڵ��ê��
	float GetAnchorY() const;

	// ��ȡ�ڵ��С
	Size GetSize() const;

	// ��ȡ�ڵ�������ű���
	float GetScaleX() const;

	// ��ȡ�ڵ��������ű���
	float GetScaleY() const;

	// ��ȡ�ڵ������б�Ƕ�
	float GetSkewX() const;

	// ��ȡ�ڵ�������б�Ƕ�
	float GetSkewY() const;

	// ��ȡ�ڵ���ת�Ƕ�
	float GetRotation() const;

	// ��ȡ�ڵ�͸����
	float GetOpacity() const;

	// ��ȡ�ڵ�����
	Property GetProperty() const;

	// ��ȡ�������
	Property GetExtrapolate() const;

	// ��ȡ�ڵ���ײ��
	Collider * GetCollider();

	// ��ȡ���ڵ�
	Node * GetParent() const;

	// ��ȡ�ڵ����ڳ���
	Scene * GetParentScene() const;

	// ���ýڵ��Ƿ���ʾ
	void SetVisible(
		bool value
	);

	// ���ýڵ�����
	void SetName(
		const String& name
	);

	// ���ýڵ������
	virtual void SetPosX(
		float x
	);

	// ���ýڵ�������
	virtual void SetPosY(
		float y
	);

	// ���ýڵ�����
	virtual void SetPos(
		const Point & point
	);

	// ���ýڵ�����
	virtual void SetPos(
		float x,
		float y
	);

	// �ڵ�����̶�
	virtual void SetPosFixed(
		bool fixed
	);

	// �ƶ��ڵ�
	virtual void Move(
		float x,
		float y
	);

	// �ƶ��ڵ�
	virtual void Move(
		const Point & v
	);

	// ���ýڵ��ͼ˳��
	// Ĭ��Ϊ 0
	virtual void SetOrder(
		int order
	);

	// ���ú������ű���
	// Ĭ��Ϊ 1.0
	virtual void SetScaleX(
		float scale_x
	);

	// �����������ű���
	// Ĭ��Ϊ 1.0
	virtual void SetScaleY(
		float scale_y
	);

	// �������ű���
	// Ĭ��Ϊ (1.0, 1.0)
	virtual void SetScale(
		float scale_x,
		float scale_y
	);

	// �������ű���
	// Ĭ��Ϊ 1.0
	virtual void SetScale(
		float scale
	);

	// ���ú�����б�Ƕ�
	// Ĭ��Ϊ 0
	virtual void SetSkewX(
		float skew_x
	);

	// ����������б�Ƕ�
	// Ĭ��Ϊ 0
	virtual void SetSkewY(
		float skew_y
	);

	// ������б�Ƕ�
	// Ĭ��Ϊ (0, 0)
	virtual void SetSkew(
		float skew_x,
		float skew_y
	);

	// ������ת�Ƕ�
	// Ĭ��Ϊ 0
	virtual void SetRotation(
		float rotation
	);

	// ����͸����
	// Ĭ��Ϊ 1.0, ��Χ [0, 1]
	virtual void SetOpacity(
		float opacity
	);

	// ����ê��ĺ���λ��
	// Ĭ��Ϊ 0, ��Χ [0, 1]
	virtual void SetAnchorX(
		float anchor_x
	);

	// ����ê�������λ��
	// Ĭ��Ϊ 0, ��Χ [0, 1]
	virtual void SetAnchorY(
		float anchor_y
	);

	// ����ê��λ��
	// Ĭ��Ϊ (0, 0), ��Χ [0, 1]
	virtual void SetAnchor(
		float anchor_x,
		float anchor_y
	);

	// �޸Ľڵ���
	virtual void SetWidth(
		float width
	);

	// �޸Ľڵ�߶�
	virtual void SetHeight(
		float height
	);

	// �޸Ľڵ��С
	virtual void SetSize(
		float width,
		float height
	);

	// �޸Ľڵ��С
	virtual void SetSize(
		Size size
	);

	// ���ýڵ�����
	virtual void SetProperty(
		Property prop
	);

	// ���û�ر���Ⱦ����ü�
	virtual void SetClipEnabled(
		bool enabled
	);

	// ���ýڵ��Ե��ɫ
	virtual void SetBorderColor(
		const Color& color
	);

	// �жϵ��Ƿ��ڽڵ���
	bool ContainsPoint(
		const Point& point
	);

	// �ж��������Ƿ��ཻ
	bool Intersects(
		Node * node
	);

	// ����ӽڵ�
	void AddChild(
		Node * child,
		int order = 0		/* ��Ⱦ˳�� */
	);

	// ��Ӷ���ӽڵ�
	void AddChild(
		const Nodes& nodes,	/* �ڵ����� */
		int order = 0		/* ��Ⱦ˳�� */
	);

	// ��ȡ����������ͬ���ӽڵ�
	Nodes GetChildren(
		const String& name
	) const;

	// ��ȡ������ͬ���ӽڵ�
	Node* GetChild(
		const String& name
	) const;

	// ��ȡ�����ӽڵ�
	const Nodes& GetAllChildren() const;

	// ��ȡ�ӽڵ�����
	int GetChildrenCount() const;

	// �Ƴ��ӽڵ�
	bool RemoveChild(
		Node * child
	);

	// �Ƴ�����������ͬ���ӽڵ�
	void RemoveChildren(
		const String& child_name
	);

	// �Ƴ����нڵ�
	void RemoveAllChildren();

	// �Ӹ��ڵ��Ƴ�
	void RemoveFromParent();

	// ִ�ж���
	void RunAction(
		Action * action
	);

	// ��������
	void ResumeAction(
		const String& name
	);

	// ��ͣ����
	void PauseAction(
		const String& name
	);

	// ֹͣ����
	void StopAction(
		const String& name
	);

	// ����������ͣ����
	void ResumeAllActions();

	// ��ͣ���ж���
	void PauseAllActions();

	// ֹͣ���ж���
	void StopAllActions();

	// ��ȡ���ж���
	const Actions& GetAllActions() const;

	// ˢ�¶�������
	void UpdateActionsTime();

	// �ַ������Ϣ
	virtual bool Dispatch(
		const MouseEvent& e,
		bool handled
	);

	// �ַ�������Ϣ
	virtual bool Dispatch(
		const KeyEvent& e,
		bool handled
	);

	// �����ڵ�
	virtual void Visit();

protected:
	E2D_DISABLE_COPY(Node);

	// ��Ⱦ�ڵ��Ե
	void DrawBorder();

	// ��Ⱦ��ײ������
	void DrawCollider();

	// ���ýڵ����ڳ���
	void SetParentScene(
		Scene * scene
	);

	// �ӽڵ�����
	void SortChildren();

	// ����ת������
	void UpdateTransform();

	// ���½ڵ�͸����
	void UpdateOpacity();

	// ���¶���
	void UpdateActions();

protected:
	String		name_;
	size_t		hash_name_;
	Point		pos_;
	Size		size_;
	Point		scale_;
	Point		anchor_;
	Point		skew_;
	float		rotation_;
	float		display_opacity_;
	float		real_opacity_;
	int			order_;
	bool		visible_;
	bool		clip_enabled_;
	bool		need_sort_;
	bool		need_transform_;
	bool		fixed_position_;
	Collider	collider_;
	Scene *		parent_scene_;
	Node *		parent_;
	Property	extrapolate_;
	Color		border_color_;
	Actions		actions_;
	Nodes		children_;
	ID2D1Geometry*		border_;
	D2D1::Matrix3x2F	initial_matrix_;
	D2D1::Matrix3x2F	final_matrix_;
};


// ����
class Scene :
	public Node
{
public:
	Scene();

	virtual ~Scene();

	// ���볡��
	virtual void OnEnter() {}

	// �˳�����
	virtual void OnExit() {}

	// �رմ���
	// ˵�������� false ����ֹ���ڹر�
	virtual bool OnCloseWindow() { return true; }

	// ��ʾ�����ؽڵ��Ե
	// Ĭ�ϣ�����
	void ShowBorder(
		bool visible
	);

	// ��ʾ��������ײ��
	// Ĭ�ϣ�����
	void ShowCollider(
		bool visible
	);

	// �����ڵ�
	virtual void Visit() override;

protected:
	E2D_DISABLE_COPY(Scene);

protected:
	bool border_visible_;
	bool collider_visible_;
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
		const Rect& crop_rect	/* �ü����� */
	);

	explicit Sprite(
		const String& file_name
	);

	explicit Sprite(
		const String& file_name,
		const Rect& crop_rect	/* �ü����� */
	);

	virtual ~Sprite();

	// ����ͼƬ�ļ�
	bool Open(
		const Resource& res
	);

	// ����ͼƬ�ļ�
	bool Open(
		const String& file_name
	);
	
	// ����ͼƬ
	bool Open(
		Image * image
	);

	// ��ͼƬ�ü�Ϊ����
	void Crop(
		const Rect& crop_rect	/* �ü����� */
	);

	// ��ȡ Image ����
	Image * GetImage() const;

	// ��Ⱦ����
	virtual void Draw() const override;

protected:
	E2D_DISABLE_COPY(Sprite);

protected:
	Image * image_;
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
		bool		wrap;				// ���Զ�����
		float		wrap_width;			// �Զ����п��
		float		line_spacing;		// �м��
		bool		underline;			// �»���
		bool		strikethrough;		// ɾ����
		bool		outline;			// ��ʾ���
		Color		outline_color;		// �����ɫ
		float		outline_width;		// ����߿�
		Stroke		outline_stroke;		// ������ཻ��ʽ

	public:
		Style();

		Style(
			Color color,
			Align alignment = Align::Left,
			bool wrap = false,
			float wrap_width = 0.f,
			float line_spacing = 0.f,
			bool underline = false,
			bool strikethrough = false,
			bool outline = true,
			Color outline_color = Color(Color::Black, 0.5),
			float outline_width = 1.f,
			Stroke outline_stroke = Stroke::Round
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
	const String& GetText() const;

	// ��ȡ����
	const Font& GetFont() const;

	// ��ȡ�ı���ʽ
	const Style& GetStyle() const;

	// ��ȡ������
	const String& GetFontFamily() const;

	// ��ȡ��ǰ�ֺ�
	float GetFontSize() const;

	// ��ȡ��ǰ�����ϸֵ
	UINT GetFontWeight() const;

	// ��ȡ������ɫ
	const Color& GetColor() const;

	// ��ȡ�����ɫ
	const Color& GetOutlineColor() const;

	// ��ȡ����߿�
	float GetOutlineWidth() const;

	// ��ȡ������ཻ��ʽ
	Stroke GetOutlineStroke() const;

	// ��ȡ�ı���ʾ����
	int GetLineCount() const;

	// �Ƿ���б��
	bool IsItalic() const;

	// �Ƿ���ʾɾ����
	bool strikethrough() const;

	// �Ƿ���ʾ�»���
	bool underline() const;

	// �Ƿ���ʾ���
	bool outline() const;

	// �����ı�
	void SetText(
		const String& text
	);

	// �����ı���ʽ
	void SetStyle(
		const Style& style
	);

	// ��������
	void SetFont(
		const Font& font
	);

	// ����������
	void SetFontFamily(
		const String& family
	);

	// �����ֺţ�Ĭ��ֵΪ 22��
	void SetFontSize(
		float size
	);

	// ���������ϸֵ��Ĭ��ֵΪ Text::Font::Weight::Normal��
	void SetFontWeight(
		UINT weight
	);

	// ����������ɫ��Ĭ��ֵΪ Color::WHITE��
	void SetColor(
		Color color
	);

	// ��������б�壨Ĭ��ֵΪ false��
	void SetItalic(
		bool value
	);

	// �򿪻�ر��ı��Զ����У�Ĭ��Ϊ�رգ�
	void SetWrapEnabled(
		bool wrap
	);

	// �����ı��Զ����еĿ�ȣ�Ĭ��Ϊ 0��
	void SetWrapWidth(
		float wrap_width
	);

	// �����м�ࣨĬ��Ϊ 0��
	void SetLineSpacing(
		float line_spacing
	);

	// ���ö��뷽ʽ��Ĭ��Ϊ Align::Left��
	void SetAlignment(
		Align align
	);

	// �����»��ߣ�Ĭ��ֵΪ false��
	void SetUnderline(
		bool underline
	);

	// ����ɾ���ߣ�Ĭ��ֵΪ false��
	void SetStrikethrough(
		bool strikethrough
	);

	// �����Ƿ���ʾ���
	void SetOutline(
		bool outline
	);

	// ���������ɫ
	void SetOutlineColor(
		Color outline_color
	);

	// ��������߿�
	void SetOutlineWidth(
		float outline_width
	);

	// ����������ཻ��ʽ
	void SetOutlineStroke(
		Stroke outline_stroke
	);

	// ��Ⱦ����
	virtual void Draw() const override;

protected:
	E2D_DISABLE_COPY(Text);

	// �����Ű�����
	void Reset();

	// �������ָ�ʽ��
	void CreateFormat();

	// �������ֲ���
	void CreateLayout();

protected:
	String	text_;
	Font	font_;
	Style	style_;
	IDWriteTextFormat * text_format_;
	IDWriteTextLayout * text_layout_;
};


class Button :
	public Node
{
public:
	Button();

	explicit Button(
		Node * normal,					/* ��ͨ״̬ */
		const Function& func = nullptr	/* ��ť�����Ļص����� */
	);

	explicit Button(
		Node * normal,					/* ��ͨ״̬ */
		Node * selected,				/* ��갴��״̬ */
		const Function& func = nullptr	/* ��ť�����Ļص����� */
	);

	explicit Button(
		Node * normal,					/* ��ͨ״̬ */
		Node * mouseover,				/* �������״̬ */
		Node * selected,				/* ��갴��״̬ */
		const Function& func = nullptr	/* ��ť�����Ļص����� */
	);

	explicit Button(
		Node * normal,					/* ��ͨ״̬ */
		Node * mouseover,				/* �������״̬ */
		Node * selected,				/* �������״̬ */
		Node * disabled,				/* ��ť����״̬ */
		const Function& func = nullptr	/* ��ť�����Ļص����� */
	);

	// ��ȡ��ť״̬�����û��ǽ���
	bool IsEnable() const;

	// ���ð�ť���û����
	void SetEnabled(
		bool enabled
	);

	// ����һ���������ʾ�İ�ť
	virtual void SetNormal(
		Node * normal
	);

	// ����������밴ťʱ��ʾ�İ�ť
	virtual void SetMouseOver(
		Node * mouseover
	);

	// ������갴�°�ťʱ��ʾ�İ�ť
	virtual void SetSelected(
		Node * selected
	);

	// ���ð�ť������ʱ��ʾ�İ�ť
	virtual void SetDisabled(
		Node * disabled
	);

	// ���ð�ť�����Ļص�����
	void SetCallbackOnClick(
		const Function& func
	);

	// ����ê��λ��
	// Ĭ��Ϊ (0, 0), ��Χ [0, 1]
	virtual void SetAnchor(
		float anchor_x,
		float anchor_y
	) override;

	// �ַ������Ϣ
	virtual bool Dispatch(
		const MouseEvent& e,
		bool handled
	) override;

	// �����ڵ�
	virtual void Visit() override;

protected:
	E2D_DISABLE_COPY(Button);

	// ��ť״̬ö��
	enum class Status { Normal, Mouseover, Selected };

	// ���ð�ť״̬
	virtual void SetStatus(
		Status status
	);

	// ˢ�°�ť��ʾ
	virtual void UpdateVisible();

	// ����ص�
	virtual void OnClick();

protected:
	Node *		normal_;
	Node *		mouseover_;
	Node *		selected_;
	Node *		disabled_;
	bool		enabled_;
	bool		is_selected_;
	Status		status_;
	Function	callback_;
};


class ToggleButton :
	public Button
{
public:
	ToggleButton();

	explicit ToggleButton(
		Node * normal_on,				/* ��ť��ʱ����ͨ״̬ */
		Node * normal_off,				/* ��ť�ر�ʱ����ͨ״̬ */
		const Function& func = nullptr	/* ��ť�����Ļص����� */
	);

	explicit ToggleButton(
		Node * normal_on,				/* ��ť��ʱ����ͨ״̬ */
		Node * normal_off,				/* ��ť�ر�ʱ����ͨ״̬ */
		Node * selected_on,				/* ��ť��ʱ����갴��״̬ */
		Node * selected_off,			/* ��ť�ر�ʱ����갴��״̬ */
		const Function& func = nullptr	/* ��ť�����Ļص����� */
	);

	explicit ToggleButton(
		Node * normal_on,				/* ��ť��ʱ����ͨ״̬ */
		Node * normal_off,				/* ��ť�ر�ʱ����ͨ״̬ */
		Node * mouseover_on,			/* ��ť��ʱ���������״̬ */
		Node * mouseover_off,			/* ��ť�ر�ʱ���������״̬ */
		Node * selected_on,				/* ��ť��ʱ����갴��״̬ */
		Node * selected_off,			/* ��ť�ر�ʱ����갴��״̬ */
		const Function& func = nullptr	/* ��ť�����Ļص����� */
	);

	explicit ToggleButton(
		Node * normal_on,				/* ��ť��ʱ����ͨ״̬ */
		Node * normal_off,				/* ��ť�ر�ʱ����ͨ״̬ */
		Node * mouseover_on,			/* ��ť��ʱ���������״̬ */
		Node * mouseover_off,			/* ��ť�ر�ʱ���������״̬ */
		Node * selected_on,				/* ��ť��ʱ����갴��״̬ */
		Node * selected_off,			/* ��ť�ر�ʱ����갴��״̬ */
		Node * disabled_on,				/* ��ť��ʱ������״̬ */
		Node * disabled_off,			/* ��ť�ر�ʱ������״̬ */
		const Function& func = nullptr	/* ��ť�����Ļص����� */
	);

	// ��ȡ����״̬
	bool IsChecked() const;

	// ���ÿ��ذ�ť��״̬
	void SetChecked(
		bool checked
	);

	// ���ð�ť��״̬����ʾ�İ�ť
	virtual void SetNormal(
		Node * normal
	) override;

	// ���ð�ť��״̬�£�������밴ťʱ��ʾ�İ�ť
	virtual void SetMouseOver(
		Node * mouseover
	) override;

	// ���ð�ť��״̬�£���갴�°�ťʱ��ʾ�İ�ť
	virtual void SetSelected(
		Node * selected
	) override;

	// ���ð�ť��״̬�£�������ʱ��ʾ�İ�ť
	virtual void SetDisabled(
		Node * disabled
	) override;

	// ���ð�ť�ر�״̬����ʾ�İ�ť
	void SetNormalOff(
		Node * normal
	);

	// ���ð�ť�ر�״̬�£�������밴ťʱ��ʾ�İ�ť
	void SetMouseOverOff(
		Node * mouseover
	);

	// ���ð�ť�ر�״̬�£���갴�°�ťʱ��ʾ�İ�ť
	void SetSelectedOff(
		Node * selected
	);

	// ���ð�ť�ر�״̬�£���ť������ʱ��ʾ�İ�ť
	void SetDisabledOff(
		Node * disabled
	);

	// ����ê��λ��
	// Ĭ��Ϊ (0, 0), ��Χ [0, 1]
	virtual void SetAnchor(
		float anchor_x,
		float anchor_y
	) override;

protected:
	E2D_DISABLE_COPY(ToggleButton);

	// ˢ�°�ť����
	virtual void UpdateStatus();

	// ִ�а�ť��������
	virtual void OnClick() override;

protected:
	Node*	normal_on_;
	Node*	mouseover_on_;
	Node*	selected_on_;
	Node*	disabled_on_;
	Node*	normal_off_;
	Node*	mouseover_off_;
	Node*	selected_off_;
	Node*	disabled_off_;
	bool	checked_;
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
	bool IsEnable() const;

	// ��ȡ�˵��еİ�ť����
	size_t GetButtonCount() const;

	// ���ò˵����û����
	void SetEnabled(
		bool enabled
	);

	// ��Ӱ�ť
	void AddButton(
		Button * button
	);

	// �Ƴ���ť
	bool RemoveButton(
		Button * button
	);

	// ��ȡ���а�ť
	const std::vector<Button*>& GetAllButtons() const;

protected:
	E2D_DISABLE_COPY(Menu);

protected:
	bool enabled_;
	std::vector<Button*> buttons_;
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
	void SetLineColor(
		const Color& color
	);

	// ���������ɫ
	void SetFillColor(
		const Color& color
	);

	// �����������
	void SetStrokeWidth(
		float width
	);

	// ���������ཻ��ʽ
	void SetStrokeStyle(
		Stroke strokeStyle
	);

	// ��ȡ������ɫ
	Color GetLineColor() const;

	// ��ȡ�����ɫ
	Color GetFillColor() const;

	// ��ȡ�������
	float GetStrokeWidth() const;

	// ��ȡ�����ཻ��ʽ
	Stroke GetStrokeStyle() const;

	// ��ֱ��
	void DrawLine(
		const Point& begin,
		const Point& end
	);

	// ��Բ�α߿�
	void DrawCircle(
		const Point& center,
		float radius
	);

	// ����Բ�α߿�
	void DrawEllipse(
		const Point& center,
		float radius_x,
		float radius_y
	);

	// �����α߿�
	void DrawRect(
		const Rect& rect
	);

	// ��Բ�Ǿ��α߿�
	void DrawRoundedRect(
		const Rect& rect,
		float radius_x,
		float radius_y
	);

	// ���Բ��
	void FillCircle(
		const Point& center,
		float radius
	);

	// �����Բ��
	void FillEllipse(
		const Point& center,
		float radius_x,
		float radius_y
	);

	// ������
	void FillRect(
		const Rect& rect
	);

	// ���Բ�Ǿ���
	void FillRoundedRect(
		const Rect& rect,
		float radius_x,
		float radius_y
	);

protected:
	E2D_DISABLE_COPY(Canvas);

protected:
	float	stroke_width_;
	Stroke	stroke_;
	ID2D1RenderTarget * render_target_;
	ID2D1SolidColorBrush * fill_brush_;
	ID2D1SolidColorBrush * line_brush_;
	ID2D1StrokeStyle * stroke_style_;
};

}