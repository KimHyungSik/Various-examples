
import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.ArrayList;

public class MainAdapter extends RecyclerView.Adapter<MainAdapter.ViewHolder> {
    private ArrayList<ListData> mData = null;
    private GetBitmap getBitmap;
    private Context context;

    MainAdapter(ArrayList<ListData> list, Context context){
        this.mData = list;
        this.context = context;
        getBitmap = new GetBitmap();
    }

    @NonNull
    @Override
    public MainAdapter.ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.recycleritem, parent, false);
        ViewHolder holder = new ViewHolder(view);
        return holder;
    }

    @Override
    public void onBindViewHolder(@NonNull MainAdapter.ViewHolder holder, int position) {
        holder.imageView.setImageBitmap(getBitmap.asstsRead(mData.get(position).getFilename(), context));
        holder.textView.setText(String.valueOf(mData.get(position).getCount()));
    }

    @Override
    public int getItemCount() {
        return (null != mData ? mData.size() : 0);
    }

    public class ViewHolder extends RecyclerView.ViewHolder{
        protected TextView textView;
        protected ImageView imageView;
        ViewHolder(View itemView){

            super(itemView);
            textView =  itemView.findViewById(R.id.recycleText);
            imageView = itemView.findViewById(R.id.recycleImage);
        }
    }
}