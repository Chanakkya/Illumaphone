const fetch = require('node-fetch'); // Import the 'node-fetch' module

const fieldNames = ['field1', 'field2', 'field3', 'field4', 'field5', 'field6']; // Names of fields in your ThingSpeak channel

const fetchData = async () => {
  try {
    const response = await fetch(`https://api.thingspeak.com/channels/2477130/feeds.json?api_key=54DUXE673QSAII0A&results=2`);
    const data = await response.json();

    // Process the data
    let musicGenerated = false; // Flag to indicate if music is generated
    data.feeds.forEach(feed => {
      fieldNames.forEach((fieldName, index) => {
        const fieldValue = parseInt(feed[fieldName]);
        if (fieldValue > 100) {
          musicGenerated = true; // Set the flag if any field value is greater than 100
        }
      });
    });

    // Check if music is generated and print message
    if (musicGenerated) {
      console.log('Music generated');
    }
  } catch (error) {
    console.error('Error fetching data:', error);
  }
};

// Fetch data every 15 seconds
setInterval(fetchData, 15000);
