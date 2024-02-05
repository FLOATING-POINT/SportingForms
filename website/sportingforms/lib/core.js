jQuery(document).ready(function($) {

	var domain  = 'http://sportingforms.flpdigital.com/'; 	
	if(document.domain == 'localhost') domain = "http://localhost/flpdigital.com/sportingforms"; 

	var bg_image = domain+"/img/bg.png";
	$.supersized({
		slides  :  	[ {image : bg_image, title : ''} ]
	});

	$('#welcome h1').fitText(1.6);
	$('#welcome h2').fitText(4.6);

	function pulseIn(){

		$('#supersized img').stop().animate(
			{'opacity':'1.0'				
			},
			{duration: 5000, 
			easing: 'easeInOutCirc',
			complete: function(){
				pulseOut();
			}
		});

	}

	function pulseOut(){

		$('#supersized img').stop().animate(
			{'opacity':'0.75'				
			},
			{duration: 5000, 
			easing: 'easeInOutCirc',
			complete: function(){
				pulseIn();
			}
		});
		
	}
	//pulseOut();

});