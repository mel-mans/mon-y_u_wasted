import easyocr
import re
import os

reader = easyocr.Reader(['en'])
image_dir = r'C:\Path\To\Your\Images'  # <-- Update this
image_extensions = ('.png', '.jpg', '.jpeg', '.bmp', '.tiff')
total_sum = 0.0

for filename in os.listdir(image_dir):
    if filename.lower().endswith(image_extensions):
        image_path = os.path.join(image_dir, filename)
        print(f"\n📄 Processing: {filename}")

        try:
            results = reader.readtext(image_path, detail=0)
            full_text = ' '.join(results)

            found_numbers = re.findall(r'-?\d+\.\d+', full_text)

            for num_str in found_numbers:
                value = float(num_str)
                total_sum += value
                print(f"➕ Found value: {value}")

        except Exception as e:
            print(f"❌ Error processing {filename}: {e}")

print("\n========================")
print(f"🧮 Total Sum of All Decimal Values: {total_sum:.2f}")
print("========================")
