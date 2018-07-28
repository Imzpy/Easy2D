#pragma once
#include "e2dnode.h"

namespace e2d
{


// ��״
class Shape :
	public Node
{
public:
	// ��״��ʽ
	enum class Style
	{
		Solid,		/* ��� */
		Round,		/* ���� */
		Fill,		/* ���� + ��� */
	};

public:
	Shape();

	virtual ~Shape();

	// ��ȡ��ʽ
	Style getStyle() const;

	// ��ȡ�����ɫ
	Color getFillColor() const;

	// ��ȡ������ɫ
	Color getLineColor() const;

	// ��ȡ�������
	float getStrokeWidth() const;

	// ���������ɫ
	void setFillColor(
		Color fillColor
	);

	// ����������ɫ
	void setLineColor(
		Color lineColor
	);

	// �����������
	void setStrokeWidth(
		float strokeWidth
	);

	// ������ʽ
	void setStyle(Style style);

	// ���������ཻ��ʽ
	void setLineJoin(
		LineJoin lineJoin
	);

	// ��Ⱦ��״
	virtual void onRender() const override;

protected:
	E2D_DISABLE_COPY(Shape);

	// ��Ⱦ����
	virtual void _renderLine() const = 0;

	// ��Ⱦ���ɫ
	virtual void _renderFill() const = 0;

protected:
	Style	_style;
	float	_strokeWidth;
	Color	_lineColor;
	Color	_fillColor;
	ID2D1StrokeStyle * _strokeStyle;
};


// ����
class RectShape :
	public Shape
{
public:
	RectShape();

	explicit RectShape(
		Size size		/* ��Ⱥ͸߶� */
	);

	explicit RectShape(
		Point topLeft,	/* ���Ͻ����� */
		Size size		/* ��Ⱥ͸߶� */
	);

	virtual ~RectShape();

protected:
	E2D_DISABLE_COPY(RectShape);

	// ��Ⱦ����
	virtual void _renderLine() const override;

	// ��Ⱦ���ɫ
	virtual void _renderFill() const override;
};


// Բ�Ǿ���
class RoundRectShape :
	public Shape
{
public:
	RoundRectShape();

	explicit RoundRectShape(
		Size size,		/* ��Ⱥ͸߶� */
		float radiusX,	/* Բ�ǰ뾶 */
		float radiusY	/* Բ�ǰ뾶 */
	);

	explicit RoundRectShape(
		Point topLeft,	/* ���Ͻ����� */
		Size size,		/* ��Ⱥ͸߶� */
		float radiusX,	/* Բ�ǰ뾶 */
		float radiusY	/* Բ�ǰ뾶 */
	);

	virtual ~RoundRectShape();

	// ��ȡԲ�ǰ뾶
	float getRadiusX() const;

	// ��ȡԲ�ǰ뾶
	float getRadiusY() const;

	// ����Բ�ǰ뾶
	virtual void setRadiusX(
		float radiusX
	);

	// ����Բ�ǰ뾶
	virtual void setRadiusY(
		float radiusY
	);

protected:
	E2D_DISABLE_COPY(RoundRectShape);

	// ��Ⱦ����
	virtual void _renderLine() const override;

	// ��Ⱦ���ɫ
	virtual void _renderFill() const override;

protected:
	float _radiusX;
	float _radiusY;
};


// Բ��
class CircleShape :
	public Shape
{
public:
	CircleShape();

	explicit CircleShape(
		float radius	/* �뾶 */
	);

	explicit CircleShape(
		Point center,	/* Բ������ */
		float radius	/* �뾶 */
	);

	virtual ~CircleShape();

	// ��ȡ�뾶
	float getRadius() const;

	// ���ð뾶
	virtual void setRadius(
		float radius
	);

protected:
	E2D_DISABLE_COPY(CircleShape);

	// ��Ⱦ����
	virtual void _renderLine() const override;

	// ��Ⱦ���ɫ
	virtual void _renderFill() const override;

protected:
	float _radius;
};


// ��Բ��
class EllipseShape :
	public Shape
{
public:
	EllipseShape();

	explicit EllipseShape(
		float radiusX,	/* ����뾶 */
		float radiusY	/* ����뾶 */
	);

	explicit EllipseShape(
		Point center,	/* Բ������ */
		float radiusX,	/* ����뾶 */
		float radiusY	/* ����뾶 */
	);

	virtual ~EllipseShape();

	// ��ȡ����뾶
	float getRadiusX() const;

	// ��ȡ����뾶
	float getRadiusY() const;

	// ���ú���뾶
	virtual void setRadiusX(
		float radiusX
	);

	// ��������뾶
	virtual void setRadiusY(
		float radiusY
	);

protected:
	E2D_DISABLE_COPY(EllipseShape);

	// ��Ⱦ����
	virtual void _renderLine() const override;

	// ��Ⱦ���ɫ
	virtual void _renderFill() const override;

protected:
	float _radiusX;
	float _radiusY;
};

}