The objective of our project is to realize an exchange platform at the UTC.
- The project will integrate goods and services.
- The project will integrate actions of donations, exchanges or sales as well as a management of an internal currency without going into the details of a currency.
- Users will be able to post offers or requests.
- The ads can be classified according to headings but also keywords.
- We will also add mechanisms of bidding and negotiation by interposed messaging between users.



An ad will be composed of :

    - Id : String in UNIQUE
    - Date Submitted : timestamp
    - Title : String in NOT NULL
    - Photo[0..3]: File
    - Description : String
    - status valider : boolean

Thus a user will be represented in this way:

    - Username : String in UNIQUE
    - Name : String in NOT NULL
    - First name : String in NOT NULL
    - Date_Birth : Date in NOT NULL
    - Tel : Integer in UNIQUE
    - Mail : String in UNIQUE NOT NULL
    - Average_grade : float
    - City : String
    - postal code : Integer
    - status valider : boolean
    
As we don't manage deliveries, knowing the city alone is enough.

Characteristic of a good or object :

    - Reference : Integer in UNIQUE
    - Name : String
    - State : {new, good, average, bad}
    - Size : {small, medium, large, very large}
    - Year : numeric(4,0)
    - Description : String
 
 An ad can concern a sale (with a price), a service (with a price per hour) or an auction.
 
 An auction is composed of :

    - Start_price : Float
    - Duration : Integer (in days)
    - End_Date : Function (Date_Depot + Duration)
    - Current_Price
    
A sale is composed only of the attributes of the ad.
A service, in addition to the attributes of the ad is described by a service type.

A **field** will be a way to classify the ads and thus be able to search them:

    - Name: String in UNIQUE NOT NULL

A **messaging system** can be used to facilitate exchanges between users:

    - Message reference : Integer in UNIQUE
    - Message content : String
    - Date and time of sending: timestamp
    - Status: {sent, received, read}


An **evaluation** may be issued at the time of a transaction between a user and an announcement:

    - Rating: 0..5
    - Comment : String

A **transaction** will have :

    - An Identifier : String in UNIQUE
    - A Date : date
    - A Description : String

There will also be a management of a **wallet** with :

    - Amount : Integer
    - A supply
    - A recovery

An **administrator** can also validate or delete an ad or a user, he will have a pseudo in String and in UNIQUE (⚠️ He will not be a user).

Keywords will be added in order to carry out research on the advertisements.
