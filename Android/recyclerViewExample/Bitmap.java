import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

import java.io.IOException;
import java.io.InputStream;

public class GetBitmap {
    public Bitmap asstsRead(String file, Context mContext){
        InputStream is;
        Bitmap bitmap = null;
        try {
            is = mContext.getAssets().open(file);
            int size = is.available();
            byte[] buffer = new byte[size];
            is.read(buffer);
            is.close();

            bitmap = BitmapFactory.decodeByteArray(buffer, 0, buffer.length);
            bitmap = Bitmap.createScaledBitmap(bitmap, 300, 340, true);

        }catch (IOException e){
            e.printStackTrace();
        }
        return bitmap;
    }
}
