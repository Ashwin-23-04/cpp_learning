#include<iostream>

class MediaPlayer{
    public:
        virtual void play(std::string audioType, std::string fileName) = 0;
};

class AdvancedMediaPlayer {
    public:
        virtual void playVlc(std::string fileName) {}
        virtual void playMp4(std::string fileName) {}
};

class VLCPlayer : public AdvancedMediaPlayer {
    public:
        void playVlc(std::string fileName){
            std::cout << "Playing VLC file " << fileName << std::endl ;
        }
};

class MP4Player : public AdvancedMediaPlayer {
    public:
        void playMp4(std::string fileName){
            std::cout << "Playing Mp4 file " << fileName << std::endl ;
        }
};

class MediaAdapter : public MediaPlayer{
    private:
        AdvancedMediaPlayer *advancedMusicPlayer;
    public:
        void play(std::string audioType, std::string fileName){
            if(audioType.compare("vlc") == 0){
                advancedMusicPlayer = new VLCPlayer;
                advancedMusicPlayer->playVlc(fileName);
            }else if(audioType.compare("mp4") == 0){
                advancedMusicPlayer = new MP4Player;
                advancedMusicPlayer->playMp4(fileName);
            }
        }
};

class AudioPlayer : public MediaPlayer{
    MediaAdapter mediaAdapter;
    public:
        void play(std::string audioType, std::string fileName){
            if(audioType.compare("mp3") == 0){
                std::cout << "Playing Mp3 file " << fileName << std::endl;
            }else if(audioType.compare("vlc") == 0 || audioType.compare("mp4") == 0){
                mediaAdapter.play(audioType, fileName);
            }else{
                std::cout << "Invalid Audio Type " << audioType << std::endl;
            }
        }
};


int main(){
    AudioPlayer audioPlayer;
    audioPlayer.play("mp3", "something.mp3");
    audioPlayer.play("mp4", "something.mp4");
    audioPlayer.play("vlc", "something.vlc");
    audioPlayer.play("avi", "something.avi");
    return 0;
}