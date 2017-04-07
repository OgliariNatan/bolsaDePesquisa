#ifdef ADC_H_INCLUDED
#define ADC_H_INCLUDED

//#define DEBUG

void adc_init();
ISR(ADC_vect);

#endif //ADC_H_INCLUDED