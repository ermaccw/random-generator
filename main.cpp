// Random generator 随机数生成器 by Wcai
#include <QtWidgets>
#include <random>

class RandomNumberGenerator : public QWidget {
public:
    RandomNumberGenerator(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle(tr("随机数生成器 by Wcai"));
        // 设置标题栏图标
        setWindowIcon(QIcon(":/new/prefix1/ICO"));

        // 创建标签和输入框
        QLabel *labelNum = new QLabel(tr("个数:"));
        numLineEdit = new QLineEdit("5");
        numLineEdit->setValidator(new QIntValidator);

        QLabel *labelSize = new QLabel(tr("取值范围(min, max):"));
        minLineEdit = new QLineEdit("0");
        minLineEdit->setValidator(new QDoubleValidator);
        maxLineEdit = new QLineEdit("100");
        maxLineEdit->setValidator(new QDoubleValidator);

        QLabel *labelSeparator = new QLabel(tr("分隔符:"));
        separatorLineEdit = new QLineEdit(",");

        // 创建布局
        QHBoxLayout *minMaxLayout = new QHBoxLayout;
        minMaxLayout->addWidget(minLineEdit);
        minMaxLayout->addWidget(maxLineEdit);

        // 创建按钮
        generateButton = new QPushButton(tr("生成"));
        connect(generateButton, &QPushButton::clicked, this, &RandomNumberGenerator::generateNumbers);

        // 创建文本框
        resultTextEdit = new QTextEdit;
        resultTextEdit->setReadOnly(true);
        QFont resultTextFont("Microsoft YaHei UI", 14);
        resultTextEdit->setFont(resultTextFont);

        // 布局
        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(labelNum);
        layout->addWidget(numLineEdit);
        layout->addWidget(labelSize);
        layout->addLayout(minMaxLayout);
        layout->addWidget(labelSeparator);
        layout->addWidget(separatorLineEdit);
        layout->addWidget(generateButton);
        layout->addWidget(resultTextEdit);
        setLayout(layout);

        resize(450, 300); // 设置窗口大小

        // 默认生成一组随机数
        generateNumbers();
    }

private slots:
    void generateNumbers() {
        // 生成随机数
        int numCount = numLineEdit->text().toInt();
        double minValue = minLineEdit->text().toDouble();
        double maxValue = maxLineEdit->text().toDouble();
        QString separator = separatorLineEdit->text();

        // 使用随机数引擎生成随机数
        std::random_device rd;
        std::mt19937 gen(rd());

        QStringList numbers;
        for (int i = 0; i < numCount; ++i) {
            double randomNumber;
            if (minLineEdit->text().contains('.') || maxLineEdit->text().contains('.')) {
                std::uniform_real_distribution<> dis(minValue, maxValue);
                randomNumber = dis(gen);
            } else {
                std::uniform_int_distribution<> dis(minValue, maxValue);
                randomNumber = dis(gen);
            }
            numbers.append(QString::number(randomNumber));
        }

        // 将随机数用分隔符连接成字符串并显示在文本框中
        resultTextEdit->setText(numbers.join(separator));
    }

private:
    QLineEdit *numLineEdit;
    QLineEdit *minLineEdit;
    QLineEdit *maxLineEdit;
    QLineEdit *separatorLineEdit;
    QPushButton *generateButton;
    QTextEdit *resultTextEdit;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    RandomNumberGenerator generator;
    generator.show();
    return app.exec();
}
