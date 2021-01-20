# Getting started with Airtable


<details>
<summary>Creating account on Airtable - Creating Base </summary>

<h3> 1. Go to https://airtable.com </h3>
</br>
</br> 

![login screen](/Lesson_5/images/airtable_welcome.png)

</br>
</br>

<h3> 2. Sign in if you have an Airtable account, or Sign up to create a new account</h3>
</br>
</br> 

![sign up screen](/Lesson_5/images/signup.png)![sign in screen](/Lesson_5/images/signin.png)

<h3> 3. Click on Add a base and Start from scratch   </h3>     

![add base screen](/Lesson_5/images/addbase.png)

<h3> and give it a suitable name</h3> 

![name base screen](/Lesson_5/images/namebase.png)
        
<h3> 4. This will open up your new document . Note the names of the Table and Fields </h3>
        
![table view screen](/Lesson_5/images/tableview.png)
</details>



<details>
  <summary>Finding the BaseID </summary>

<h3> 1. Go to https://airtable.com/api </h3>

![api welcome screen](/Lesson_5/images/apiwelcome.png)

<h3> 2. Click on your project name to reveal the api page. Copy the Base ID and replace the "ATdocID" in secrets.py with this string </h3>

![api page screen](/Lesson_5/images/apipage.png)

</details>



<details>
  <summary>Creating the API Key</summary>


<h3> 1. Go to https://airtable.com/account and click Generate API Key</h3>

![api welcome screen](/Lesson_5/images/apikey1.png)

<h3> 2. Copy the API Key and replace the "ATappkey" in secrets.py with this string. Do not share this string.</h3>

![api welcome screen](/Lesson_5/images/apikey2.png)

</details>

# Setting up Teachable Machine on PC

Download the TeachableAudio.html file from <i> On PC </i> folder. 



 <details>
 <summary> 1.	Train your Teachable Machine code. </summary>

 <br>
 <br> 

 Go to https://teachablemachine.withgoogle.com/ and click on Get Started button

 <br>
 <br> 

 ![Getting started](/Lesson_5/images/getstarted.png)

 <br>
 <br> 
 </details>

 <details>

 <summary> 2.	Select the Audio Project</summary>

 <br>
 <br> 

 ![audio project](/Lesson_5/images/audioproject.png)

 <br>
 <br> 

 </details>

 <details>

 <summary> 3.	Record sounds to train your model  </summary>

 <br>
 <br> 

 Click on the microphone button to start recording. Record more samples for accuracy. Then click the Train Model button.

 <br>
 <br> 

 ![trainingscreen](/Lesson_5/images/trainingscreen1.png)

 <br>
 <br> 

 </details>

 <details>

 <summary> 4. Export your Model.  </summary>

 <br>
 <br> 

 Once you have recorded all samples and trained your data, click Export Model.

 <br>
 <br> 

 ![trainedscreen](/Lesson_5/images/trainedscreen.png)

 <br>
 <br> 

 </details>

 <details>

 <summary> 5. Get the model url  </summary>

 <br>
 <br>  

 Click on the Upload/Update my cloud model to create or update your model url. Copy the url from this page. Save it somewhere safe so that you can access it again later.

 <br>
 <br> 

 ![update](/Lesson_5/images/update.png)

 <br>
 <br> 

 </details>

 <details>

 <summary> 6.	Running the TeachableAudio.html file. </summary>

 <br>
 <br>  

Open the TeachableAudio.html file from "on PC" and run on Google Chrome. 

Enter the url from Step 5 in the text box saying <i>url</i>.
Also enter the API Key and Base ID for your  Airtable document in their respective boxes. Refer to the sections <i> Finding the BaseID </i> and <i> Creating API Key </i> above on where to find them.

<br>
<br>
Click submit to begin. This tab must remain open and active while you are running Lesson 5 on your EV3. 


 <br>
 <br> 

 ![apiupdate](/Lesson_5/images/htmlnew.png)

 <br>
 <br> 
 
 <i>Note: If you have  edited the Table name and Field name on your Airtable you will have to edit the html file and update the "Editable Section" . </i>

 <br>
 <br>
 </details>



<details>
 
<summary> Optional: editing the html file:</summary>
 
<br>
<br> 
<i> please proceed with caution...</i>

If you want to edit the html file or want to see how the code is written,  right-click and open the html file on an editor. 

<br>
<br> 


 </details>
 
# Setting up the library on EV3

Download the airtable.py, secrets.py, demo.py and main.py file from <i> On EV3 </i> folder and save them on your projects folder on EV3.

<details>
  <summary>Using the library</summary>
   
<h3> 0. Download secrets.py and airtable.py to your EV3.</h3>


<h3> 1. Edit the secrets.py file</h3>

Edit the secrets.py file by replacing BaseID and API Key from your account. Refer to the sections <i> Finding the BaseID </i> and <i> Creating API Key </i> above on how to do it.

<h3> 2. Understand the demo.py file</h3>

The demo.py file contains information on how to use the available Airtable functions. You may not need to use all of them, but it is useful to know what else you can do. 

In summary, you will use Get_AT and Get_AT_field functions to read single or full set of records, you will use Put_AT to create a record and Delete_AT to delete a record.

<details>
<summary>Put_AT</summary>
        
Put_AT('Table_name','Field_name','Record_value') 
Put_AT function adds a record in the Field_name Field of the  Table_name Table with the value Record_value
The function returns the record id for the updated record (useful for deleting)

</details>
<details>
        
<summary>Get_AT</summary>

Get_AT('Table_name','Field_name') returns the last record from the Field_name Field of the Table_name Table.   

</details>
<details>
<summary>Get_AT_field</summary>
        
Get_AT_field('Table_name','Field_name') returns the entire list of record from the Field_name Field of the Table_name Table. The return value will be a list. Users will need to use indexing to access individual records. use [-1] to access the last record. 

</details>
<details>
<summary>Delete_AT</summary>

Delete_AT('Table_name',"record_id")  deletes the  record with "record_id" from the Table_name Table.

</details>

<h3> 3. Edit the main.py file</h3>

You can start playing with the library using main.py. It shows how you can import airtable library and use the available function. 


</details>
