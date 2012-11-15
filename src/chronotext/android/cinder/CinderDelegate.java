
package chronotext.android.cinder;

import android.app.Activity;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import chronotext.android.cinder.CinderRenderer;
import chronotext.android.gl.GLView;

public class CinderDelegate
{
  protected Activity mActivity;
  protected Handler mHandler;

  protected GLView mView;

  public CinderDelegate(Activity activity, Handler handler)
  {
    mActivity = activity;
    mHandler = handler;

    mView = new GLView(activity);
    mView.setRenderer(new CinderRenderer(activity, this)); // WILL START THE RENDERER'S THREAD
  }

  public GLView getView()
  {
    return mView;
  }

  public void showView()
  {
    if (mView.getVisibility() == View.GONE)
    {
      mView.setVisibility(View.VISIBLE);
    }
  }

  public void hideView()
  {
    if (mView.getVisibility() == View.VISIBLE)
    {
      mView.setVisibility(View.GONE);
    }
  }

  // ---------------------------------------- TO BE CALLED FROM THE HOST ACTIVITY ----------------------------------------

  public void onPause()
  {
    mView.onPause();
  }

  public void onResume()
  {
    mView.onResume();
  }

  public void onDestroy()
  {
    mView.onDestroy();
  }

  // ---------------------------------------- MESSAGING SYSTEM ----------------------------------------

  /*
   * THIS WILL BE SENT ON THE RENDERER'S THREAD
   */
  public void sendMessage(int what, String body)
  {
    mView.sendMessage(what, body);
  }

  /*
   * THIS IS RECEIVED ON THE RENDERER'S THREAD
   */
  public void handleMessage(int what, String body)
  {
    mHandler.sendMessage(Message.obtain(mHandler, what, body));
  }
}
