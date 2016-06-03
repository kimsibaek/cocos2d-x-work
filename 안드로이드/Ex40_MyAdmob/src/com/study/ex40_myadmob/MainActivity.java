package com.study.ex40_myadmob;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.InterstitialAd;

import android.annotation.TargetApi;
import android.app.Activity;
import android.graphics.Color;
import android.graphics.Point;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.Display;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.LinearLayout;

public class MainActivity extends Activity {

	private AdView adView;
	private InterstitialAd interstitialAd;
	private AdRequest adRequest;
	
//	private static final String AD_UNIT_ID = "ca-app-pub-0000000000000000/0000000000";
	private static final String AD_UNIT_ID = "ca-app-pub-4370782412404568/5556576732";
	private static final String AD_UNIT_ID_FULL = "ca-app-pub-4370782412404568/1567029131";
	
	// Helper get display screen to avoid deprecated function use
	private Point getDisplaySize(Display d)
    {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB)
        {
            return getDisplaySizeGE11(d);
        }
        return getDisplaySizeLT11(d);
    }
    @TargetApi(Build.VERSION_CODES.HONEYCOMB_MR2)
    private Point getDisplaySizeGE11(Display d)
    {
        Point p = new Point(0, 0);
        d.getSize(p);
        return p;
    }
    private Point getDisplaySizeLT11(Display d)
    {
        try
        {
            Method getWidth = Display.class.getMethod("getWidth", new Class[] {});
            Method getHeight = Display.class.getMethod("getHeight", new Class[] {});
            return new Point(((Integer) getWidth.invoke(d, (Object[]) null)).intValue(),
            		         ((Integer) getHeight.invoke(d, (Object[]) null)).intValue());
        }
        catch (NoSuchMethodException e2) // None of these exceptions should ever occur.
        {
            return new Point(-1, -1);
        }
        catch (IllegalArgumentException e2)
        {
            return new Point(-2, -2);
        }
        catch (IllegalAccessException e2)
        {
            return new Point(-3, -3);
        }
        catch (InvocationTargetException e2)
        {
            return new Point(-4, -4);
        }
    }

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main_activity);
	
	
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

		int width = getDisplaySize(getWindowManager().getDefaultDisplay()).x;

		LinearLayout.LayoutParams adParams = new LinearLayout.LayoutParams(
		width,
		LinearLayout.LayoutParams.WRAP_CONTENT);


		adView = new AdView(this);
		adView.setAdSize(AdSize.BANNER);
		adView.setAdUnitId(AD_UNIT_ID);


		adRequest = new AdRequest.Builder()
		.addTestDevice(AdRequest.DEVICE_ID_EMULATOR)
//		.addTestDevice("HASH_DEVICE_ID")
		.addTestDevice("71A5DC7424A7D2578625C4CD8634E7A3")
		.build();

		adView.loadAd(adRequest);
        adView.setBackgroundColor(Color.BLACK);
        adView.setBackgroundColor(0);
        addContentView(adView, adParams);

        
		Button button1 = (Button)findViewById(R.id.button1);
		button1.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v)
			{
				showAd();
			}
		});

		Button button2 = (Button)findViewById(R.id.button2);
		button2.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v)
			{
				hideAd();
			}
		});

		// ----------------------------------------------------------------
		// ª¿‘ ±§∞Ì
		interstitialAd = new InterstitialAd(this);
		interstitialAd.setAdUnitId(AD_UNIT_ID_FULL);

	    interstitialAd.setAdListener(new AdListener() {
	    	@Override
	    	public void onAdLoaded() {
	    		Log.d("study", "onAdLoaded");
	        
	    		if (interstitialAd.isLoaded()) {
	    			interstitialAd.show();
	    		} else {
	    			Log.d("study", "Interstitial ad was not ready to be shown.");
	    		}
	    	}

	    	@Override
	    	public void onAdFailedToLoad(int errorCode) {
	    		String message = String.format("onAdFailedToLoad (%s)", getErrorReason(errorCode));
	    		Log.d("study", message);
	    	}
	    });

	    Button button3 = (Button)findViewById(R.id.button3);
		button3.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v)
			{
			    // ª¿‘ ±§∞Ì ∑ŒµÂ Ω√¿€
		    	interstitialAd.loadAd(adRequest);
			}
		});

	}

    public void hideAd()
    {
		if (adView.isEnabled())
			adView.setEnabled(false);
		if (adView.getVisibility() != 4 )
			adView.setVisibility(View.INVISIBLE);
    }

    public void showAd()
    {
		if (!adView.isEnabled())
			adView.setEnabled(true);
		if (adView.getVisibility() == 4 )
			adView.setVisibility(View.VISIBLE);	
    }

    @Override
    protected void onResume() {
    	super.onResume();
    	if (adView != null) {
    		adView.resume();
    	}
    }
    
    /** Gets a string error reason from an error code. */
    private String getErrorReason(int errorCode) {
    	String errorReason = "";
    	switch(errorCode) {
        case AdRequest.ERROR_CODE_INTERNAL_ERROR:
        	errorReason = "Internal error";
        	break;
        case AdRequest.ERROR_CODE_INVALID_REQUEST:
        	errorReason = "Invalid request";
        	break;
        case AdRequest.ERROR_CODE_NETWORK_ERROR:
        	errorReason = "Network Error";
        	break;
        case AdRequest.ERROR_CODE_NO_FILL:
        	errorReason = "No fill";
        	break;
    	}
    	return errorReason;
    }
    
}



