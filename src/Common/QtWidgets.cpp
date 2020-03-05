#include "QtWidgets.hpp"

//_______________________________________________________________
RadioGroup::RadioGroup(std::string groupLabel, int numPerRow, int selectedInx) : QGroupBox(QString::fromStdString(groupLabel)), numPerRow(numPerRow) {
    buttonGroup = new QButtonGroup();
    gridLayout = new QGridLayout();
    setLayout(gridLayout);
    connect(buttonGroup, static_cast<void(QButtonGroup::*)(QAbstractButton *)>(&QButtonGroup::buttonClicked),[=](QAbstractButton *button){ 
        emit Modified();
    });
}

void RadioGroup::SetValue(int index)
{
    foreach(QAbstractButton *button, buttonGroup->buttons()) {
        if (buttonGroup->id(button) == index)
        {
            button->setChecked(true);
            break;
        }
    }
}

void RadioGroup::AddButton(std::string txt, int index) {
    QRadioButton* button = new QRadioButton(QString::fromStdString(txt));
    int i = buttons.size();
    int xInx = i % numPerRow;
    int yInx = i / numPerRow;
    gridLayout->addWidget(button, yInx, xInx);   
    buttonGroup->addButton(button, index);
    buttons.push_back(button);
}

int RadioGroup::GetValue() {
    return buttonGroup->checkedId();
}


void RadioGroup::Disable() {
    for(int i =0; i<buttons.size(); i++) { 
        buttons[i]->setEnabled(false);
    }
}

void RadioGroup::Enable() {
    for(int i =0; i<buttons.size(); i++) { 
        buttons[i]->setEnabled(true);
    }        

}

//_______________________________________________________________


//CustomSlider class
//____________________________________________________________
//
CustomSlider::CustomSlider(float min, float max, float step, std::string label, float initialValue) : QGroupBox(QString::fromStdString(label)) {
    QHBoxLayout* mainLayout = new QHBoxLayout();
    setLayout(mainLayout);

    this->step = step;
    this->min = min;
    this->max = max;

    slider = new QSlider(Qt::Horizontal);
    slider->setMinimum(min / step);
    slider->setMaximum(max / step);
    slider->setSingleStep(1);
    slider->setValue(initialValue/ step);
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(OnSliderChanged(int)));
    mainLayout->addWidget(slider);

    spinBox = new QDoubleSpinBox();
    spinBox->setMinimum(min);
    spinBox->setMaximum(max);
    spinBox->setSingleStep(step);
    spinBox->setDecimals(5);
    spinBox->setValue(initialValue);

    // connect(spinBox, SIGNAL(valueChanged(double)), this, SLOT(OnSpinBoxChanged(double)));
    mainLayout->addWidget(spinBox);
}

int CustomSlider::GetValue() {
    double value = spinBox->value();
    return 0;
}

void CustomSlider::SetVisible(bool visible) {
    SetVisible(visible);
}
