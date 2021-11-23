#ifndef INCLUDED_TITLE
#define	INCLUDED_TITLE

class Title : public Scene
{
public:
	static Title* instance() { return &instance_; }

	void init();
	void update();
	void draw();

	UIManager*			uiManager() { return uiManager_; }
private:

	UIManager*			uiManager_;
	static Title instance_;
};

#endif // !INCLUDED_TITLE
