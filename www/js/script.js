function speak(message) {
  console.log(message);
  var msg = new SpeechSynthesisUtterance(message);
  msg.rate = 0.2;
  window.speechSynthesis.speak(msg);

  var voices = window.speechSynthesis.getVoices();
  console.log(voices);
}
