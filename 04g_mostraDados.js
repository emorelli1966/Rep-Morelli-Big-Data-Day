db.dados_sensores.aggregate( [ { $unwind : "$events" },  { "$project": { "_id": 0 }}, { "$out": "dados" } ] )
var m = db.dados.find({},{"events.event.value":1,"events.event.when":1,_id:0});
m.forEach ( function( n ) { print ("Valor: " + n.events.event.value + " - Quando: " + n.events.event.when); } ) 