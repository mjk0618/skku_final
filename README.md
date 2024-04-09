# SKKU 종합설계프로젝트 9조
## 👫 Members
강민재, 박준서, 이규식, 최원석

## 📄 Abstract
치매 환자 부양 가정을 위한 스마트락 시스템

## 💻 Methods
### Face Recognition
Pre-trained Face Recognition 모델을 활용하여 입력된 이미지에 대한 Vector Representation을 얻고, 유사도를 비교하여 환자 식별

### Speech Recognition
FR 단계에서 식별된 환자에게 사전에 등록된 질문을 던지고 받은 답변을 처리하여 잠금장치 활성화 여부를 결정 (TTS, STT, Language Model 사용)
