#include <QtWidgets>


class MyBoardWidget : public QWidget {
public:
    MyBoardWidget(QWidget* parent = nullptr) : QWidget(parent) {
        setMinimumSize(400, 400);
        setAutoFillBackground(true);
        mIsDrawing = false;
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(QPen(Qt::black, 2));
        painter.setBrush(Qt::white);
        painter.drawRect(rect());
    }

    void mousePressEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            mIsDrawing = true;
            mPath = QPainterPath(event->pos());
            update();
        }
    }

    void mouseMoveEvent(QMouseEvent* event) override {
        if (mIsDrawing) {
            mPath.lineTo(event->pos());
            update();
        }
    }

    void mouseReleaseEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            mIsDrawing = false;
        }
    }

private:
    bool mIsDrawing;
    QPainterPath mPath;
};