package com.study.ex18_mylist6;

import java.util.ArrayList;

import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.Button;

public class SingerAdapter extends BaseAdapter {

	Context context;
	
	ArrayList<SingerItem> items = new ArrayList<SingerItem>();
	
	public SingerAdapter(Context context){
		this.context = context;
	}
	
	public void addItem(SingerItem item){
		items.add(item);
	}
	
	public int getCount(){
		return items.size();
	}
	
	public Object getItem(int position){
		return items.get(position);
	}
	
	public long getItemId(int position){
		return position;
	}
	
	public View getView(int position, View convertView, ViewGroup parent){
		
		SingerItemView view = null;
		if(convertView == null){
			view = new SingerItemView(context);
		}else{
			view = (SingerItemView) convertView;
		}
		
		final SingerItem item = items.get(position);
		view.setName(item.getName());
		view.setTel(item.getTelnum());
		view.setImage(item.getResId());
		
		Button button1 = (Button)view.findViewById(R.id.button1);
		button1.setFocusable(false);
		button1.setOnClickListener(new Button.OnClickListener() {
			
			public void onClick(View v){
				String str = "tel :" + item.getTelnum();
				
				Log.d("gikimi", str);
				
				Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse(str));
				context.startActivity(intent);
			}
		});
		
		return view;
	}
}
