#pragma once

#include "Common.h"

//_______________________________________________________________
class RadioGroup : public QGroupBox {
    Q_OBJECT
    public:
        std::vector<QRadioButton*> buttons;
        QButtonGroup* buttonGroup;
        QGridLayout *gridLayout;
        int numPerRow;
        RadioGroup(std::string groupLabel, int numPerRow, int selectedInx);

        void SetValue(int index);

        void AddButton(std::string txt, int index);
        int GetValue();
        void Disable();
        void Enable();

        signals: 
            void Modified();
};

//_______________________________________________________________

class CustomSlider : public QGroupBox {
	Q_OBJECT
public:
	QSlider* slider;
	QDoubleSpinBox* spinBox;
	float step;
	float min;
	float max;
	CustomSlider(float min, float max, float step, std::string label, float initialValue);

	int GetValue();

	void SetVisible(bool visible);


public slots:
	void OnSpinBoxChanged(double i)
	{
		slider->setValue(i / step);
	}

	void OnSliderChanged(int i)
	{
		double val = (double)i * step;
		spinBox->setValue(val);
		emit Modified(val);
	}

signals:
	void Modified(double val);
};