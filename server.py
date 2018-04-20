from spyne import Application, rpc, ServiceBase, Iterable, Integer, Unicode

from spyne.protocol.soap import Soap11
from spyne.server.wsgi import WsgiApplication
import boto3


class HelloWorldService(ServiceBase):
    @rpc(Unicode, Integer, _returns=Iterable(Unicode))
    def say_hello(ctx, name, times):
        a = times.split(",")
        lat = a[0]
        lon = a[1]
##        dynamodb = boto3.resource('dynamodb',
##                        aws_access_key_id='AKIAI7HHEQFZZ6KQ536A',
##                        aws_secret_access_key='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'
##                        , region_name='us-east-2')
##        dynamodb_client = boto3.client('dynamodb', aws_access_key_id = 'AKIAI7HHEQFZZ6KQ536A',
##                        aws_secret_access_key = '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',
##                        region_name = 'us-east-2')
##
##        table_name = 'ItemTracker_tbl'
##        existing_tables = dynamodb_client.list_tables()['TableNames']
##
##        if table_name not in existing_tables:
##
##        # Create the DynamoDB table.
##
##            table = dynamodb.create_table(TableName='table_name',
##                                          KeySchema=[{'AttributeName': 'itemtrackerId'
##                                          , 'KeyType': 'HASH'}],
##                                          AttributeDefinitions=[{'AttributeName': 'itemtrackerId'
##                                          , 'AttributeType': 'S'}],
##                                          ProvisionedThroughput={'ReadCapacityUnits': 5,
##                                          'WriteCapacityUnits': 5})
##
##            # Wait until the table exists.
##
##            table.meta.client.get_waiter('table_exists').wait(TableName='table_name')
##
##        table = dynamodb.Table['ItemTracker_tbl']
##        response  = table.query(KeyConditionExpression=Key('itemtrackerId').eq('123'))
##
##        if response['count'] >0:
##            table.update_item(Key={'itemtrackerId': name},
##                              UpdateExpression='SET lat = list_append(lat, :i)'
##                              , ExpressionAttributeValues={':i': [lat]},
##                              ReturnValues='UPDATED_NEW')
##            table.update_item(Key={'itemtrackerId': name},
##                              UpdateExpression='SET lon = list_append(lon, :i)'
##                              , ExpressionAttributeValues={':i': [lon]},
##                              ReturnValues='UPDATED_NEW')
##        else:
##            table.put_item(Item={
##                'itemtrackerId':name,
##                'lat':[lat],
##                'lon':[lon]
##                })

    

application = Application([HelloWorldService], 'spyne.examples.hello.soap',
                          in_protocol=Soap11(validator='lxml'),
                          out_protocol=Soap11())

wsgi_application = WsgiApplication(application)


if __name__ == '__main__':
    import logging

    from wsgiref.simple_server import make_server

    logging.basicConfig(level=logging.DEBUG)
    logging.getLogger('spyne.protocol.xml').setLevel(logging.DEBUG)

    logging.info("listening to http://127.0.0.1:8000")
    logging.info("wsdl is at: http://localhost:8000/?wsdl")

    server = make_server('127.0.0.1', 8000, wsgi_application)
    server.serve_forever()
