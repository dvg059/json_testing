# C++ programming exercise

In this exercise you be evaluated for your ability to problem solve, create high quality code, and accurately implement requirements from instructions. It is important that you read this file carefully and pay attention to details.

You are encouraged to ask as many questions as you like.

Your instructions are as follows:

* Review the business requirements
* Setup a C++ project with CMake (preferred), or other tool chain.
* Implement the application to meet business requirements.
  * Take care to consider not only style & clarity, but also extensibility
  * You may use boost, qt, or other libraries you want to.
  * Automated unit tests are not required but are appreciated.
* Share the git repository for this exercise. It should include a README file, with instructions for compling and running your program. The project should be compilable on a common linux distribution.

# Business requirements

Build an application that can parse input from a file and implement the rules from a decision table to build the correct output payload that mimics the representation of a mobile push notification. The input and output structure are defined for you below.

The application must take a parameter pointing to a json file as input. A sample input.json file is included in this prompt, and will be a list of json objects each with the following fields:
* module - a string representing the algorithm of the external process that generated the result
* rulesEngineEnabled - a boolean flag that specifies whether the result was evaluated by the rules engine. A rules engine is a separate component that examines various thresholds in a result, and determines whether the result can be considered 'positive' or 'negative'.
* rulesEngineTriggered - a boolean flag that specifies whether the rules engine crossed the configured threshold for the result, and can therefore be considered a 'Positive' result. If the rules engine is not enabled, this field will not be present in the input dictionary (i.e. undefined).
* siteName - a string representing the site where the result originated. If siteName is missing, None or empty, the function must throw an error

Note that the sample input.json file is only a sample file, and does not include all possible inputs. Your code should correctly handle a longer input.json file containing more input fields.

When invoked with valid input as per above, the application must print to standard output (std::cout) a json object for each input payload in the list. This output must have two fields:
* message - a string that is the title of the push notification
* loudTone - a boolean value that indicates whether to use a loud tone or a quieter, default tone with the push notification

## Example input:
```
{
  "module": "CTA",
  "rulesEngineEnabled": true,
  "rulesEngineTriggered": false,
  "siteName": "North California Community Hospital"
}
```

## Expected output:
```
{
  "message": "Negative CT Angiography result at North California Community Hospital",
  "loudTone": false
}
```

## Decision table (range of expected inputs)
Inputs outside of this range should throw an error

|  Module 	| Rules engine enabled 	| Rules engine triggered 	|                  Expected message                 	| Expected Loud tone 	|
|:-------:	|:--------------------:	|:----------------------:	|:-------------------------------------------------:	|:------------------:	|
|   CTA   	|         false        	|        N/A       	|    New CT Angiography result at {siteName}   	|        false       	|
|   CTA   	|         true         	|          false         	| Negative CT Angiography result at {siteName} 	|        false       	|
|   CTA   	|         true         	|          true          	| Positive CT Angiography result at {siteName} 	|        true        	|
|    MR   	|         false        	|        N/A       	|          New MR Result at {siteName}         	|        false       	|
|    MR   	|         true         	|          false         	|           Negative MR at {siteName}          	|        false       	|
|    MR   	|         true         	|          true          	|           Positive MR at {siteName}          	|        true        	|
|   CTP   	|         false        	|        N/A       	|     New CT Perfusion result at {siteName}    	|        false       	|
|   CTP   	|         true         	|          false         	|  Negative CT Perfusion result at {siteName}  	|        false       	|
|   CTP   	|         true         	|          true          	|  Positive CT Perfusion result at {siteName}  	|        true        	|
|   ICH   	|         false        	|        N/A       	|  New hemorrhage module result at {siteName}  	|        false       	|
|   ICH   	|         true         	|          false         	|         Negative hemorrhage module result at {siteName}         	|        false       	|
|   ICH   	|         true         	|          true          	|         Positive hemorrhage module result at {siteName}         	|        true        	|
| ASPECTS 	|         false        	|        N/A       	|                 New ASPECTS score at {siteName}                 	|        false       	|
| ASPECTS 	|         true         	|          false         	|                 High ASPECTS score at {siteName}                	|        false       	|
| ASPECTS 	|         true         	|          true          	|                 Low ASPECTS score at {siteName}                 	|        true        	|
